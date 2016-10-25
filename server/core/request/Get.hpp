//
// Get.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 03:52:17 2016 stephane galibert
// Last update Tue Oct 25 16:24:32 2016 stephane galibert
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
