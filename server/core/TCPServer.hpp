//
// TCPServer.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:06:52 2016 stephane galibert
// Last update Mon Nov  7 17:27:06 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "AServer.hpp"

#include "AConnection.hpp"
#include "TCPConnection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

class TCPServer : public AServer
{
public:
  TCPServer(boost::asio::io_service &io_service, int port,
	    RequestHandler &req, ServerConfig &config, PluginManager &pm);
  virtual ~TCPServer(void);

  virtual void init(void);

  virtual void open(void);
  virtual void close(void);

private:
  void accept(void);

  void do_accept(std::shared_ptr<TCPConnection> ptr,
		 boost::system::error_code const& ec);

  boost::asio::ssl::context _context;
  boost::asio::ip::tcp::acceptor _acceptor;

  ConnectionManager _coManager;
};
