//
// Dump.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 07:25:50 2016 stephane galibert
// Last update Tue Oct 25 15:05:07 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "ICommand.hpp"

class Dump : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<Packet *(AConnection::shared)> Cmds;
public:
  Dump(void);
  virtual ~Dump(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
private:
  Packet *plugin(AConnection::shared own);
  std::unordered_map<std::string, Cmds> _cmds;
};
