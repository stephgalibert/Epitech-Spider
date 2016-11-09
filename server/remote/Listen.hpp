//
// Listen.hpp for server in /home/galibe_s/rendu/Spider/server/remote
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Nov  9 05:18:06 2016 stephane galibert
// Last update Wed Nov  9 05:42:35 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <signal.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "Protocol.hpp"

class Listen
{
public:
  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLSocket;
public:
  Listen(boost::asio::io_service &ios, SSLSocket &socket);
  ~Listen(void);

  void listen(void);

  void start(void);
  void close(void);

  void init(void);

private:
  /*void connect(void);
  void handshake(void);

  void do_connect(boost::system::error_code const& ec,
		  boost::asio::ip::tcp::resolver::iterator);
		  void do_handshake(boost::system::error_code const& ec);*/

  void signal(void);
  void do_signal(boost::system::error_code const& ec, int signo);

  Packet const *read(void);
  void write(Packet *packet);

  boost::asio::io_service &_io_service;
  /*boost::asio::ip::tcp::resolver _resolver;
    boost::asio::ssl::context _context;*/
  SSLSocket &_socket;

  boost::asio::signal_set _signals;
  boost::asio::streambuf _read;
  bool _running;
  /*std::string _remoteIP;
    std::string _remotePort;*/
};
