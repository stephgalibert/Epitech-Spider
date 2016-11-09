//
// ConnectionManager.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:47 2016 stephane galibert
// Last update Wed Nov  9 04:01:28 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <memory>

#include "AConnection.hpp"
#include "StaticTools.hpp"

class ConnectionManager
{
public:
  ConnectionManager(void);
  ~ConnectionManager(void);

  void join(AConnection::shared connection);
  void leave(AConnection::shared connection);
  void broadcast(std::string const& mac, std::string const& msg);

  void closeAll(void);
private:
  std::set<AConnection::shared> _connections;
};
