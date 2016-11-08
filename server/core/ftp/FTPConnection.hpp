//
// FTPConnection.hpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 15:53:07 2016 stephane galibert
// Last update Tue Nov  8 21:27:07 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <memory>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "PluginManager.hpp"
#include "Protocol.hpp"
#include "StaticTools.hpp"

class FTPSession;

class FTPConnection : public std::enable_shared_from_this<FTPConnection>
{
public:
  typedef boost::asio::ip::tcp::socket Socket;
public:
  FTPConnection(boost::asio::io_service &io_service,
		FTPSession &co_manager,
		PluginManager &pluginManager,
		std::string const& fname);
  ~FTPConnection(void);

  void start(void);
  void write(Packet *packet);

  Socket& socket(void);

  unsigned short createFTP(std::string const& filename);
  void deleteFTP(unsigned short port);

protected:
  void do_write(boost::system::error_code const& ec, size_t len);
  void do_read(boost::system::error_code const& ec, size_t len);

  void write(void);
  void read(void);

  FTPSession &_co_manager;
  PluginManager &_pm;
  Socket _socket;

  boost::asio::streambuf _read;
  std::string _fname;
};
