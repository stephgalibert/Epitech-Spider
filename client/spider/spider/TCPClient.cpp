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
	_context.load_verify_file("server.crt");
	_connected = false;

	_ofs.open("debug.log", std::ios::app | std::ios::out);
}

TCPClient::~TCPClient()
{
}

void TCPClient::connect(void)
{
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
	_io_service.post([this, packet](void) -> void {
		bool writeInProgress = !_toWrites.empty();
		_toWrites.push(packet);
		if (!writeInProgress) {
			write();
		}
	});
}

void TCPClient::disconnect(void)
{
	_ofs << "disconnecting" << std::endl;
	_io_service.stop();
	if (_runThread.joinable()) {
		_runThread.join();
	}
	_connected = false;
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

void TCPClient::read(void)
{
	boost::asio::async_read(_socket, _read, boost::asio::transfer_at_least(sizeof(Packet)),
		boost::bind(&TCPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::write(void)
{
	Packet *packet = _toWrites.front();
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
		_ofs << "connected" << std::endl;
		handshake();
	} else {
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::connect, this));
		_ofs << "Error: '" << _remote << ":" << _port << "' is inaccessible (" << ec << ")" << std::endl;
	}
}

void TCPClient::do_read(boost::system::error_code const& ec, size_t)
{
	if (!ec) {
		Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
		_read.consume(sizeof(Packet) + packet->size);

		//_ofs << "receive packet type '" + std::to_string((int)packet->type) + " with data: " << packet->data << std::endl;

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
	if (!ec) {
		_ofs << "handshake success" << std::endl;
		_connected = true;

		write(StaticTools::CreatePacket(PacketType::PT_NewClient, StaticTools::GetMacAddress()));
		
		read();
	}
	else {
		_ofs << "handshake failed" << std::endl;
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