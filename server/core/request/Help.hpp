//
// Help.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:52:29 2016 stephane galibert
// Last update Sat Nov  5 15:52:31 2016 stephane galibert
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
