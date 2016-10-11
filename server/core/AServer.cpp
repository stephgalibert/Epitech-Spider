//
// AServer.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 08:32:16 2016 stephane galibert
// Last update Sun Aug 21 12:11:52 2016 stephane galibert
//

#include "AServer.hpp"

AServer::AServer(boost::asio::io_service &io_service, int port)
  : _io_service(io_service),
    _port(port),
    _context(boost::asio::ssl::context::sslv23),
    _pluginManager(_config),
    _signals(_io_service)
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
  _signals.add(SIGQUIT);

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

  signal();
}

AServer::~AServer(void)
{
}

void AServer::init(void)
{
  try {
    _config.read("config.xml");
    StaticTools::LoadPlugin(_pluginManager);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void AServer::signal(void)
{
  _signals.async_wait(boost::bind(&AServer::do_signal, this,
				  boost::asio::placeholders::error,
				  boost::asio::placeholders::signal_number));
}

void AServer::do_signal(boost::system::error_code const& ec, int signo)
{
  if (!ec) {
    std::clog << std::endl << "receiving signal n°" << signo << std::endl;
    _io_service.stop();
  } else {
    std::clog << ec << std::endl;
  }
}
