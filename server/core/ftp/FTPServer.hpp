//
// FTPServer.hpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Nov  7 17:04:56 2016 stephane galibert
// Last update Tue Nov  8 21:19:58 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "FTPConnection.hpp"
#include "FTPSession.hpp"

class FTPServer
{
public:
  FTPServer(boost::asio::io_service &ios, PluginManager &pm,
	    std::string const& filename);
  ~FTPServer(void);

  void open(void);
  void close(void);

  unsigned short getPort(void) const;

  bool inUse(void) const;
  void setInUse(bool value);

  void setFilename(std::string const& fname);

private:
  void accept(void);

  void do_accept(std::shared_ptr<FTPConnection> ptr,
		 boost::system::error_code const& ec);

  boost::asio::io_service &_io_service;
  PluginManager &_pm;
  std::string _filename;

  boost::asio::ip::tcp::acceptor _acceptor;
  unsigned short _port;
  FTPSession _coManager;
  bool _inUse;
};
