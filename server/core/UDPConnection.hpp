//
// UDPConnection.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:00:50 2016 stephane galibert
// Last update Thu Nov 10 12:34:21 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <memory>

#include <boost/bind.hpp>

#include "AConnection.hpp"

class ConnectionManager;

class UDPConnection : public AConnection
{
public:
  UDPConnection(boost::asio::io_service &io_service,
		RequestHandler &reqHandler,
		PluginManager &pluginManager,
		ConnectionManager &cm,
		ServerConfig &config,
		int port);
  virtual ~UDPConnection(void);

  virtual void start(void);
  virtual void write(Packet *packet);

  virtual void addLog(std::string const& toadd);
  virtual void connectDB(void);
  virtual void disconnectDB(void);

  virtual void broadcast(std::string const& msg);
  virtual void kill(void);

protected:
  virtual void do_write(boost::system::error_code const& ec, size_t len);
  virtual void do_read(boost::system::error_code const& ec, size_t len);
  virtual void do_handshake(boost::system::error_code const& ec);

  void write(void);
  void read(void);

  boost::asio::ip::udp::socket _socket;
  boost::asio::ip::udp::endpoint _endpoint;

  boost::asio::streambuf _read;
  std::queue<Packet *> _toWrites;
};
