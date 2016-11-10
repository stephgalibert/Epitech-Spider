//
// ConnectionManager.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:57 2016 stephane galibert
// Last update Thu Nov 10 12:33:56 2016 stephane galibert
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

void ConnectionManager::broadcast(std::string const& mac, std::string const& msg)
{
    for (auto &it : _connections) {
      if (it->isListened(mac)) {
	it->write(StaticTools::CreatePacket(PacketType::PT_Response, msg));
      }
    }
}

bool ConnectionManager::kill(std::string const& mac)
{
  for (auto &it : _connections) {
    if (it->getMacAddress() == mac) {
      it->kill();
      return (true);
    }
  }
  return (false);
}

void ConnectionManager::closeAll(void)
{
  std::set<AConnection::shared>::iterator it;

  it = _connections.begin();
  while (it != _connections.end()) {
    it = _connections.erase(it);
  }
}
