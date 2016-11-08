//
// FTPSession.hpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 18:38:32 2016 stephane galibert
// Last update Tue Nov  8 18:46:00 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <memory>

#include "FTPConnection.hpp"

class FTPSession
{
public:
  FTPSession(void);
  ~FTPSession(void);

  void join(std::shared_ptr<FTPConnection> connection);
  void leave(std::shared_ptr<FTPConnection> connection);

  void closeAll(void);
private:
  std::set<std::shared_ptr<FTPConnection> > _connections;
};
