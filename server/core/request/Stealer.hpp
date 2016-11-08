//
// Stealer.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 17:48:39 2016 stephane galibert
// Last update Tue Nov  8 17:49:42 2016 stephane galibert
//

#pragma once

#include "IRequest.hpp"

class Stealer : public IRequest
{
public:
  Stealer(void);
  virtual ~Stealer(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
};
