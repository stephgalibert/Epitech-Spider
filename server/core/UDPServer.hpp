//
// UDPServer.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 09:24:22 2016 stephane galibert
// Last update Wed Aug 17 07:03:40 2016 stephane galibert
//

#pragma once


#include <iostream>
#include <string>
#include <memory>
#include <queue>

#include "AServer.hpp"

#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"
//#include "Database.hpp"

#include "StaticTools.hpp"

class UDPServer : public AServer
{
public:
  UDPServer(boost::asio::io_service &io_service, int port);
  ~UDPServer(void);

  virtual void init(void);

  virtual void open(void);
  virtual void close(void);

  void write(std::string const& data);
private:
  void receive(void);
  void do_receive(boost::system::error_code const& ec, size_t);

  void write(void);
  void do_write(void);

  boost::asio::ip::udp::socket _socket;
  boost::asio::ip::udp::endpoint _endpoint;
  boost::array<char, 1> _recv_buffer;
  std::queue<std::string> _toWrites;
};
