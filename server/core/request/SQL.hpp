//
// SQL.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 16:59:17 2016 stephane galibert
// Last update Tue Oct 25 17:00:13 2016 stephane galibert
//

#pragma once

#include <string>

#include "Protocol.hpp"
#include "ICommand.hpp"

class SQL : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
public:
  SQL(void);
  virtual ~SQL(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
};
