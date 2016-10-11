//
// Nc.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 19:26:06 2016 stephane galibert
// Last update Wed Aug 24 22:28:02 2016 stephane galibert
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

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  static std::string badParameter(void);
};
