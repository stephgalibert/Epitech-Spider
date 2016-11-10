//
// Kill.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Nov 10 11:43:41 2016 stephane galibert
// Last update Thu Nov 10 11:44:24 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Kill : public IRequest
{
public:
  Kill(void);
  virtual ~Kill(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
};
