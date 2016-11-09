//
// UDPServer.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 15:35:35 2016 stephane galibert
// Last update Tue Nov  8 23:53:40 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <queue>

#include "AServer.hpp"

#include "UDPConnection.hpp"
#include "RequestHandler.hpp"
#include "ConnectionManager.hpp"

#include "StaticTools.hpp"

class UDPServer : public AServer
{
public:
  UDPServer(boost::asio::io_service &ios, int port, RequestHandler &req,
	    ServerConfig &config, PluginManager &pm, ConnectionManager &cm);
  ~UDPServer(void);

  virtual void init(void);

  virtual void open(void);
  virtual void close(void);

private:
  std::shared_ptr<UDPConnection> _connection;
};
