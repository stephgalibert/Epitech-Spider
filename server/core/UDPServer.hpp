//
// UDPServer.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 15:35:35 2016 stephane galibert
// Last update Sun Nov  6 18:35:38 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <queue>

//#include "Protocol.hpp"
#include "AServer.hpp"

//#include "ConnectionManager.hpp"
#include "UDPConnection.hpp"
#include "RequestHandler.hpp"

#include "StaticTools.hpp"

class UDPServer : public AServer
{
public:
  UDPServer(boost::asio::io_service &io_service, int port,
	    RequestHandler &req, ServerConfig &config, PluginManager &pm);
  ~UDPServer(void);

  virtual void init(void);

  virtual void open(void);
  virtual void close(void);

  //void write(Packet *data);
private:
  /*void receive(void);
  void do_receive(boost::system::error_code const& ec, size_t);

  void write(void);
  void do_write(boost::system::error_code const& ec, size_t);

  boost::asio::ip::udp::socket _socket;
  boost::asio::ip::udp::endpoint _endpoint;
  boost::asio::streambuf _read;

  std::queue<Packet *> _toWrites;
  bool _running;*/

  std::shared_ptr<UDPConnection> _connection;
};
