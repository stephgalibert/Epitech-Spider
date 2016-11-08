//
// AServer.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 08:32:16 2016 stephane galibert
// Last update Tue Nov  8 03:13:16 2016 stephane galibert
//

#include "AServer.hpp"

AServer::AServer(boost::asio::io_service &io_service, int port,
		 RequestHandler &req, ServerConfig &config, PluginManager &pm)
  : _io_service(io_service),
    _port(port),
    _reqHandler(req),
    _config(config),
    _pluginManager(pm),
    _signals(_io_service)
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);
  _signals.add(SIGQUIT);

  signal();
}

AServer::~AServer(void)
{
}

void AServer::init(void)
{
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
    (void)signo;
    /*std::clog << std::endl << "receiving signal n°" << signo
      << " - skipped" << std::endl;*/
    _io_service.stop();
  } else {
    std::clog << ec << std::endl;
  }
}
