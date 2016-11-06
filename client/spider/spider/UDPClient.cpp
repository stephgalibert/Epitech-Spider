#include "UDPClient.h"

UDPClient::UDPClient(std::string const& ip, std::string const& port)
	: _resolver(_io_service),
	_socket(_io_service, boost::asio::ip::udp::udp::endpoint(boost::asio::ip::udp::udp::v4(), std::atoi(port.c_str()))),
	_remote(ip),
	_port(port)
{
	_debug.open("debug_udp.log", std::ios::app | std::ios::out);
}

UDPClient::~UDPClient()
{
}

void UDPClient::connect(void)
{
	boost::asio::ip::udp::udp::resolver::query query(boost::asio::ip::udp::udp::v4(), _remote, _port);

	_sender = *_resolver.resolve(query);
	read();
	StaticTools::Mac = StaticTools::GetMacAddress();
}



void UDPClient::write(Packet* packet)
{
	bool writeInProgress = !_toWrites.empty();

	_toWrites.push(packet);
	if (!writeInProgress) {
		write();
	}
}

void UDPClient::do_write(boost::system::error_code const& ec, size_t)
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

void UDPClient::read(void)
{
	_socket.async_receive_from(_read.prepare(2048), _sender,
		boost::bind(&UDPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPClient::do_read(boost::system::error_code const& ec, size_t bytes)
{
	if (!ec) {
		Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
		_read.consume(sizeof(Packet) + packet->size);
		
		if (packet) {
			if (packet->MAGIC == MAGIC_NUMBER) {
				_debug << "udp read: " << std::string(packet->data, packet->size) << std::endl;
				Packet *reply = NULL;

				_reqHandler.request(*this, packet, &reply);

				if (reply) {
					write(reply);
				}
			}
			else {
				write(StaticTools::CreatePacket(PacketType::PT_Error, "Error 50: unknown error"));
			}
		}

		if (_connected) {
			read();
		}
	}
}

void UDPClient::write(void)
{
	Packet *packet = _toWrites.front();
	_debug << "write " << std::string(packet->data, packet->size) << std::endl;
	_socket.async_send_to(boost::asio::buffer(packet, sizeof(Packet) + packet->size), _sender,
		boost::bind(&UDPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPClient::disconnect(void)
{
	_io_service.stop();
	if (_runThread.joinable()) {
		_runThread.join();
	}
	_connected = false;
}

void UDPClient::runThread(void)
{
	try {
		_io_service.run();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}

void UDPClient::run(void)
{
	_runThread = std::thread(&UDPClient::runThread, this);
}

bool UDPClient::isConnected(void) const
{
	return (true);
}

IClient &UDPClient::operator<<(Packet *packet)
{
	write(packet);
	return (*this);
}

Packet *UDPClient::createPacket(PacketType type, std::string const& data)
{
	return (StaticTools::CreateUDPPacket(type, data));
}