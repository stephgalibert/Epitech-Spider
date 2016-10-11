//
// main.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:04 2016 stephane galibert
// Last update Tue Oct  4 18:43:52 2016 chalie_a
//

#include <iostream>
#include <string>

#include <boost/asio.hpp>

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
    
    TCPServer tcp(io_service, 4242);
    UDPServer udp(io_service, 4242);

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
