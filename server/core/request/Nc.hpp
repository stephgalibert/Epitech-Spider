//
// Nc.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 17:48:43 2016 stephane galibert
// Last update Tue Nov  8 17:49:48 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Nc : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
public:
  Nc(void);
  virtual ~Nc(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
private:
  //*static std::string badParameter(void);
};
