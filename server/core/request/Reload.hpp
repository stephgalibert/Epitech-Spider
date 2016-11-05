//
// Reload.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:54:31 2016 stephane galibert
// Last update Sat Nov  5 15:54:31 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "ICommand.hpp"

class Reload : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<Packet *(AConnection::shared)> Cmds;
public:
  Reload(void);
  virtual ~Reload(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
private:
  Packet *plugin(AConnection::shared own);
  std::unordered_map<std::string, Cmds> _cmds;
};
