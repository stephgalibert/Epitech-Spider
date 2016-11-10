//
// TCPConnection.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:00:55 2016 stephane galibert
// Last update Thu Nov 10 12:30:46 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <memory>

#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "AConnection.hpp"

class ConnectionManager;

class TCPConnection : public AConnection
{
public:
  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLSocket;
public:
  TCPConnection(boost::asio::io_service &io_service,
		boost::asio::ssl::context &context,
		ConnectionManager &co_manager,
		RequestHandler &reqHandler,
		PluginManager &pluginManager,
		ServerConfig &config);
  virtual ~TCPConnection(void);

  virtual void start(void);
  virtual void write(Packet *packet);

  virtual void addLog(std::string const& toadd);
  virtual void connectDB(void);
  virtual void disconnectDB(void);

  virtual void broadcast(std::string const& msg);
  virtual void kill(void);

  SSLSocket::lowest_layer_type& socket(void);

protected:
  virtual void do_write(boost::system::error_code const& ec, size_t len);
  virtual void do_read(boost::system::error_code const& ec, size_t len);
  virtual void do_handshake(boost::system::error_code const& ec);

  void write(void);
  void read(void);
  void handshake(void);

  SSLSocket _socket;

  boost::asio::streambuf _read;
  std::queue<Packet *> _toWrites;
};
