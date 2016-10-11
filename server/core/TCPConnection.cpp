//
// TCPConnection.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:06:00 2016 stephane galibert
// Last update Wed Aug 24 17:35:04 2016 stephane galibert
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

void TCPConnection::write(std::string const& data)
{
  bool write_in_progress = !_toWrites.empty();
  _toWrites.push(data);
  if (!write_in_progress) {
    write();
  }
}

void TCPConnection::write(void)
{
  boost::asio::async_write(_socket, boost::asio::buffer(_toWrites.front()),
			   boost::bind(&AConnection::do_write,
				       shared_from_this(),
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::read(void)
{
  boost::asio::async_read(_socket, _read, boost::asio::transfer_at_least(1),
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
    std::string s((std::istreambuf_iterator<char>(&_read)),
		  std::istreambuf_iterator<char>());

    std::cout << "read: " << s << std::endl;
    std::string ret = _reqHandler.request(shared_from_this(), s);
    if (!ret.empty()) {
      write(ret);
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
