//
// Console.hpp for console in /home/galibe_s/rendu/Spider/server/plugins/UIConsole
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 16:15:32 2016 stephane galibert
// Last update Wed Nov  9 05:35:24 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <iterator>
#include <functional>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "JSONBuilder.hpp"
#include "JSONReader.hpp"
#include "Protocol.hpp"
#include "Listen.hpp"

#include "StaticTools.hpp"

class Console
{
public:
  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLSocket;
  typedef std::function<void(std::vector<std::string> const&)> Cmds;
public:
  Console(std::string const& remote, std::string const& port);
  ~Console(void);

  void start(void);
  void close(void);

  void init(void);

private:
  void run(void);
  void input(void);

  void connect(void);
  void handshake(void);

  void do_connect(boost::system::error_code const& ec,
		  boost::asio::ip::tcp::resolver::iterator);
  void do_handshake(boost::system::error_code const& ec);

  bool verify_crt(bool preverified, boost::asio::ssl::verify_context& ctx);

  Packet const *read(void);
  void write(Packet *packet);

  void cmd_help(std::vector<std::string> const& av);
  void cmd_dump(std::vector<std::string> const& av);
  void cmd_exit(std::vector<std::string> const& av);
  void cmd_reload(std::vector<std::string> const& av);
  void cmd_set(std::vector<std::string> const& av);
  void cmd_get(std::vector<std::string> const& av);
  void cmd_sql(std::vector<std::string> const& av);
  void cmd_close(std::vector<std::string> const& av);
  void cmd_listen(std::vector<std::string> const& av);
  std::map<std::string, Cmds> _cmds;

  boost::asio::io_service _io_service;
  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ssl::context _context;
  SSLSocket _socket;

  boost::thread _io_service_thread;

  boost::asio::streambuf _read;
  bool _running;
  std::string _remoteIP;
  std::string _remotePort;
};
