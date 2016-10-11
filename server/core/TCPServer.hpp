//
// TCPServer.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:06:52 2016 stephane galibert
// Last update Fri Aug 19 18:13:10 2016 stephane galibert
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
//#include "Database.hpp"

class TCPServer : public AServer
{
public:
  TCPServer(boost::asio::io_service &io_service, int port);
  ~TCPServer(void);

  virtual void init(void);

  virtual void open(void);
  virtual void close(void);

private:
  void accept(void);

  void do_accept(std::shared_ptr<TCPConnection> ptr,
		 boost::system::error_code const& ec);

  boost::asio::ip::tcp::acceptor _acceptor;

  //Database _database;
  ConnectionManager _coManager;
  RequestHandler _reqHandler;
};
