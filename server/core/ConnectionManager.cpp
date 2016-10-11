//
// ConnectionManager.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:57 2016 stephane galibert
// Last update Thu Aug 18 13:39:50 2016 stephane galibert
//

#include "ConnectionManager.hpp"

ConnectionManager::ConnectionManager(void)
{

}

ConnectionManager::~ConnectionManager(void)
{

}

void ConnectionManager::join(AConnection::shared connection)
{
  connection->start();
  _connections.insert(connection);
}

void ConnectionManager::leave(AConnection::shared connection)
{
  _connections.erase(connection);
}

void ConnectionManager::broadcast(std::string const& msg)
{
  for (auto it : _connections)
    it->write(msg);
}

void ConnectionManager::closeAll(void)
{
  std::set<AConnection::shared>::iterator it;

  it = _connections.begin();
  while (it != _connections.end()) {
    it = _connections.erase(it);
  }
}
