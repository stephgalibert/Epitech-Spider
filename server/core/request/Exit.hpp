//
// Exit.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:51:45 2016 stephane galibert
// Last update Sat Nov  5 15:51:49 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Exit : public IRequest
{
public:
  Exit(void);
  virtual ~Exit(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
};
