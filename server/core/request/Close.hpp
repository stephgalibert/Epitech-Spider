//
// Close.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Oct 26 15:09:22 2016 stephane galibert
// Last update Wed Oct 26 15:29:39 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "ICommand.hpp"

class Close : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<Packet *(AConnection::shared, Params const &)> Cmds;
public:
  Close(void);
  virtual ~Close(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
private:
  Packet *plugin(AConnection::shared own, Params const& av);
  std::unordered_map<std::string, Cmds> _cmds;
};
