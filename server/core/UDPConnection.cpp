//
// UDPConnection.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:57:27 2016 stephane galibert
// Last update Wed Nov  9 14:24:37 2016 stephane galibert
//

#include "UDPConnection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

UDPConnection::UDPConnection(boost::asio::io_service &io_service,
			     RequestHandler &reqHandler,
			     PluginManager &pluginManager,
			     ConnectionManager &cm,
			     ServerConfig &config,
			     int port)
  : AConnection(io_service, reqHandler, pluginManager, cm, config),
    _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
}

UDPConnection::~UDPConnection(void)
{
}

void UDPConnection::start(void)
{
  try {
    _running = true;
    read();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void UDPConnection::write(Packet *packet)
{
  bool write_in_progress = !_toWrites.empty();

  _toWrites.push(packet);

  if (!write_in_progress) {
    write();
  }
}

void UDPConnection::addLog(std::string const& toadd)
{
  if (toadd.size() > 11) {
    std::string mac = toadd.substr(0, toadd.find_first_of(" \t"));
    std::string data = toadd.substr(toadd.find_first_of(" \t") + 1, toadd.size() - toadd.find_first_of(" \t") + 1);

    std::clog << "mac: '" << mac << "'" << std::endl;
    std::clog << "data: '" << data << "'" << std::endl;

    _pluginManager.newConnectionDatabase(mac);
    _pluginManager.newKeyDatabase(mac, data);
  }
}

void UDPConnection::connectDB(void)
{
  if (isRegistered()) {
    _pluginManager.newConnectionDatabase(_mac);
  }
}

void UDPConnection::disconnectDB(void)
{
  if (isRegistered()) {
    _pluginManager.lostConnectionDatabase(_mac);
  }
}

void UDPConnection::broadcast(std::string const& msg)
{
  std::string mac = msg.substr(0, msg.find_first_of(" \t"));
  std::string data = msg.substr(msg.find_first_of(" \t") + 1, msg.size() - msg.find_first_of(" \t") + 1);

  _co_manager.broadcast(mac, data);
}

void UDPConnection::write(void)
{
  Packet *packet = _toWrites.front();
  _socket.async_send_to(boost::asio::buffer(packet, sizeof(Packet) + packet->size),
			_endpoint,
			boost::bind(&UDPConnection::do_write, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
}

void UDPConnection::read(void)
{
  _socket.async_receive_from(_read.prepare(1024), _endpoint,
			     boost::bind(&UDPConnection::do_read, this,
					 boost::asio::placeholders::error,
					 boost::asio::placeholders::bytes_transferred));
}

void UDPConnection::do_write(boost::system::error_code const& ec, size_t)
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

void UDPConnection::do_read(boost::system::error_code const& ec, size_t len)
{
  if (!ec) {
    Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
    _read.consume(len);

    Packet *reply = NULL;
    _reqHandler.request(shared_from_this(), packet, &reply);

    if (reply) {
      write(reply);
    }

    if (_running) {
      read();
    }
  }
  else {
    _running = false;
  }
}

void UDPConnection::do_handshake(boost::system::error_code const& ec)
{
  (void)ec;
}
