//
// main.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:04 2016 stephane galibert
// Last update Sun Nov  6 17:41:41 2016 stephane galibert
//

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "RequestHandler.hpp"
#include "ServerConfig.hpp"
#include "PluginManager.hpp"
#include "TCPServer.hpp"
#include "UDPServer.hpp"

/*  TODO
**  Code refactoring (sujet) // to continue
**  Connection Privilege // maybe ok
**  XML config // maybe ok
**  Server UDP // working at
*/
int main(void)
{
  try {
    boost::asio::io_service io_service;
    RequestHandler reqHandler;
    ServerConfig config;
    PluginManager pm(config);

    try {
      config.read("config.xml");
      StaticTools::LoadPlugin(pm);
    } catch (std::runtime_error const& e) {
      throw (e);
    }

    TCPServer tcp(io_service, 4242, reqHandler, config, pm);
    UDPServer udp(io_service, 4242, reqHandler, config, pm);

    tcp.init();
    udp.init();

    tcp.open();
    udp.open();

    io_service.run();

    tcp.close();
    udp.close();
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
