//
// Key.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 24 22:24:41 2016 stephane galibert
// Last update Tue Nov  8 23:42:39 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Key : public IRequest
{
public:
  Key(void);
  virtual ~Key(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **packet);
};
