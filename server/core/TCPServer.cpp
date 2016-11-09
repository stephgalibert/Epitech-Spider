//
// TCPServer.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:07:05 2016 stephane galibert
// Last update Tue Nov  8 23:53:13 2016 stephane galibert
//

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_service &io_service, int port,
		     RequestHandler &req, ServerConfig &config, PluginManager &pm,
		     ConnectionManager &cm)
  : AServer(io_service, port, req, config, pm, cm),
    _context(boost::asio::ssl::context::sslv23),
    _acceptor(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
  _context.set_options(boost::asio::ssl::context::default_workarounds
		       | boost::asio::ssl::context::no_sslv2
		       | boost::asio::ssl::context::single_dh_use);

  try {
    _context.use_certificate_chain_file("certificates/server.crt");
    _context.use_private_key_file("certificates/server.key",
				  boost::asio::ssl::context::pem);
  } catch (std::exception const& e) {
    std::cerr << "Unable to open server certificates: " << e.what() << std::endl;
  }
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
  accept();
}

void TCPServer::close(void)
{
  std::clog << "shuting down TCP server ..." << std::endl;
  _coManager.closeAll();
  _acceptor.close();
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
