//
// Exit.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:27:31 2016 stephane galibert
// Last update Wed Oct 19 16:20:53 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Exit : public IRequest
{
public:
  Exit(void);
  virtual ~Exit(void);

  //virtual std::string execute(AConnection::shared own, JSONReader &reader);
  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
};
