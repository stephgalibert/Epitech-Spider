//
// Console.hpp for server in /home/galibe_s/project/SpiderServer/plugins/UIConsole
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Aug  8 20:13:59 2016 stephane galibert
// Last update Mon Oct 24 12:00:49 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <thread>
#include <iterator>
#include <functional>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "JSONBuilder.hpp"
#include "JSONReader.hpp"
#include "Protocol.hpp"

#include "IUserInterface.hpp"
#include "PluginRegister.hpp"

#include "StaticTools.hpp"

PluginInfo g_info = {
  "UIConsole",
  "Stéphane GALIBERT",
  0x01
};

class Console : public IUserInterface
{
public:
  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLSocket;
  typedef std::function<void(std::vector<std::string> const&)> Cmds;
public:
  Console(void);
  virtual ~Console(void);

  virtual void start(void);
  virtual void close(void);

  virtual PluginInfo const& getPluginInfo(void) const;

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

  //std::string read(void);
  Packet *read(void);
  //void write(std::string const& data);
  void write(Packet *packet);

  /*void cmd_help(std::vector<std::string> const& av);
    void cmd_dump(std::vector<std::string> const& av);*/
  void cmd_exit(std::vector<std::string> const& av);
  /*void cmd_reload(std::vector<std::string> const& av);
  void cmd_set(std::vector<std::string> const& av);
  void cmd_get(std::vector<std::string> const& av);
  void cmd_sql(std::vector<std::string> const& av);*/
  std::map<std::string, Cmds> _cmds;

  boost::asio::io_service _io_service;
  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ssl::context _context;
  SSLSocket _socket;

  std::thread _th;
  std::thread _ui;

  boost::asio::streambuf _read;
  bool _running;
};

extern "C" void registerPlugin(std::unique_ptr<PluginRegister> &pr)
{
  std::unique_ptr<Console> ui(new Console);
  ui->init();
  pr->setUserInterface(std::move(ui));
}

extern "C" PluginInfo const& getPluginInfo(void)
{
  return (g_info);
}
