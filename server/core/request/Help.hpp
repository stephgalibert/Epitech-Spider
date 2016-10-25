//
// Help.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 10:50:55 2016 stephane galibert
// Last update Tue Oct 25 16:53:25 2016 stephane galibert
//

#pragma once

#include <string>
#include <sstream>

#include "StaticTools.hpp"
#include "Protocol.hpp"
#include "ICommand.hpp"

class Help : public ICommand
{
public:
  typedef std::shared_ptr<AConnection> Owner;

public:
  Help(void);
  virtual ~Help(void);

  virtual void execute(Owner own, JSONReader const& reader, Packet **reply);
};
