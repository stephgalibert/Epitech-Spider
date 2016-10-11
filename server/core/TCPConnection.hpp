//
// TCPConnection.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:52 2016 stephane galibert
// Last update Thu Aug 18 13:45:28 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <memory>

#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "AConnection.hpp"

//#include "Database.hpp"

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
  virtual void write(std::string const& data);

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
  std::queue<std::string> _toWrites;
};

/*void writeLog(std::string const& data);
  void setEnable(bool value);
  bool isEnabled(void) const;
  void openLogFile(void);
  void closeLogFile(void);
  std::ofstream _ofs;*/
