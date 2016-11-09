//
// main.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:04 2016 stephane galibert
// Last update Tue Nov  8 23:52:34 2016 stephane galibert
//

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "RequestHandler.hpp"
#include "ServerConfig.hpp"
#include "PluginManager.hpp"
#include "TCPServer.hpp"
#include "UDPServer.hpp"
#include "ConnectionManager.hpp"

int main(void)
{
  try {
    boost::asio::io_service io_service;
    RequestHandler reqHandler;
    ServerConfig config;
    PluginManager pm(config);
    ConnectionManager cm;

    try {
      config.read("config.xml");
      StaticTools::LoadPlugin(pm);
    } catch (std::runtime_error const& e) {
      throw (e);
    }

    pm.initDatabase();

    TCPServer tcp(io_service, 4242, reqHandler, config, pm, cm);
    UDPServer udp(io_service, 4242, reqHandler, config, pm, cm);

    tcp.init();
    udp.init();

    tcp.open();
    udp.open();

    io_service.run();

    tcp.close();
    udp.close();

    pm.closeAll();
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
