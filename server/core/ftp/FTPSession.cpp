//
// ConnectionManager.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:57 2016 stephane galibert
// Last update Tue Nov  8 18:46:05 2016 stephane galibert
//

#include "FTPSession.hpp"

FTPSession::FTPSession(void)
{

}

FTPSession::~FTPSession(void)
{

}

void FTPSession::join(std::shared_ptr<FTPConnection> connection)
{
  connection->start();
  _connections.insert(connection);
}

void FTPSession::leave(std::shared_ptr<FTPConnection> connection)
{
  _connections.erase(connection);
}

void FTPSession::closeAll(void)
{
  std::set<std::shared_ptr<FTPConnection> >::iterator it;

  it = _connections.begin();
  while (it != _connections.end()) {
    it = _connections.erase(it);
  }
}
