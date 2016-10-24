//
// TCPConnection.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:06:00 2016 stephane galibert
// Last update Mon Oct 24 12:03:25 2016 stephane galibert
//

#include "TCPConnection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

TCPConnection::TCPConnection(boost::asio::io_service &io_service,
			     boost::asio::ssl::context &context,
			     ConnectionManager &co_manager,
			     RequestHandler &reqHandler,
			     PluginManager &pluginManager,
			     ServerConfig &config)
  : AConnection(io_service, co_manager, reqHandler, pluginManager, config),
    _socket(io_service, context)
{
}

TCPConnection::~TCPConnection(void)
{
}

TCPConnection::SSLSocket::lowest_layer_type& TCPConnection::socket(void)
{
  return (_socket.lowest_layer());
}

void TCPConnection::start(void)
{
  handshake();
}

void TCPConnection::write(Packet *packet)
{
  bool write_in_progress = !_toWrites.empty();
  _toWrites.push(packet);
  if (!write_in_progress) {
    write();
  }
}

void TCPConnection::write(void)
{
  Packet *packet = _toWrites.front();
  boost::asio::async_write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size),
			   boost::bind(&AConnection::do_write,
				       shared_from_this(),
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::read(void)
{
  boost::asio::async_read(_socket, _read, boost::asio::transfer_at_least(sizeof(Packet)),
			  boost::bind(&AConnection::do_read,
				      shared_from_this(),
				      boost::asio::placeholders::error,
				      boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handshake(void)
{
  _socket.async_handshake(boost::asio::ssl::stream_base::server,
			  boost::bind(&AConnection::do_handshake, shared_from_this(),
				      boost::asio::placeholders::error));
}

void TCPConnection::do_write(boost::system::error_code const& ec, size_t)
{
  if (!ec) {

    Packet *packet = _toWrites.front();
    free(packet);

    _toWrites.pop();

    if (!_toWrites.empty()) {
      write();
    }
  }
  else {
    _co_manager.leave(shared_from_this());
  }
}

void TCPConnection::do_read(boost::system::error_code const& ec, size_t /* len */)
{
  if (!ec) {
    Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());

    std::cout << "read: " << std::endl
	      << "size: " << packet->size << std::endl
	      << "type: " << (int)packet->type << std::endl
	      << "data: " << std::string(packet->data, packet->size) << std::endl;

    _read.consume(sizeof(Packet) + (packet->size * sizeof(char)));

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
    AConnection::disconnectToDB();
    _co_manager.leave(shared_from_this());
  }
}

void TCPConnection::do_handshake(boost::system::error_code const& ec)
{
  if (!ec) {
    _running = true;
    read();
  } else {
    _co_manager.leave(shared_from_this());
  }
}
