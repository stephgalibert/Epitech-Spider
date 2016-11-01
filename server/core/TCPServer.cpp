//
// TCPServer.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:07:05 2016 stephane galibert
// Last update Tue Nov  1 20:17:08 2016 stephane galibert
//

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_service &io_service, int port)
  : AServer(io_service, port),
    _acceptor(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

TCPServer::~TCPServer(void)
{
}

void TCPServer::init(void)
{
  AServer::init();
}

void TCPServer::open(void)
{
  _pluginManager.initDatabase();
  accept();
}

void TCPServer::close(void)
{
  std::clog << "shuting down TCP server ..." << std::endl;
  _coManager.closeAll();
  _acceptor.close();
  _pluginManager.closeAll();
  std::clog << "TCP server shutdown success" << std::endl;
}

void TCPServer::accept(void)
{
  std::shared_ptr<TCPConnection> shc =
    std::make_shared<TCPConnection>(_io_service, _context, _coManager,
				    _reqHandler, _pluginManager, _config);
  _acceptor.async_accept(shc->socket(),
			 boost::bind(&TCPServer::do_accept, this, shc,
				     boost::asio::placeholders::error));
}

void TCPServer::do_accept(std::shared_ptr<TCPConnection> ptr,
			  boost::system::error_code const& ec)
{
  if (!ec) {
    _coManager.join(ptr);
    accept();
  }
  else {
    std::clog << "accept: " << ec << ": " << ec.message() << std::endl;
  }
}
