//
// Listen.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Nov  9 03:47:27 2016 stephane galibert
// Last update Wed Nov  9 03:49:35 2016 stephane galibert
//

#pragma once

#include "ICommand.hpp"

class Listen : public ICommand
{
public:
  Listen(void);
  virtual ~Listen(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
};
