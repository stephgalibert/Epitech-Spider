//
// Get.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:52:10 2016 stephane galibert
// Last update Sat Nov  5 15:52:11 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "JSONBuilder.hpp"
#include "ICommand.hpp"

class Get : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<Packet *(AConnection::shared)> Cmds;
public:
  Get(void);
  virtual ~Get(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
private:
  Packet *serverInfo(AConnection::shared own);
  std::unordered_map<std::string, Cmds> _cmds;
};
