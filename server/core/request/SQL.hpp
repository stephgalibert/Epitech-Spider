//
// SQL.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 21 22:03:30 2016 stephane galibert
// Last update Sun Aug 21 22:04:22 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class SQL : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
public:
  SQL(void);
  virtual ~SQL(void);

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  static std::string badParameter(void);
};
