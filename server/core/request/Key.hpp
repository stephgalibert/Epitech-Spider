//
// Key.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 24 22:24:41 2016 stephane galibert
// Last update Wed Aug 24 22:25:00 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Key : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
public:
  Key(void);
  virtual ~Key(void);

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  static std::string badParameter(void);
};
