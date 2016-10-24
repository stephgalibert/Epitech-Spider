//
// Help.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 10:50:55 2016 stephane galibert
// Last update Wed Oct 19 15:30:16 2016 stephane galibert
//

#pragma once

#include <string>

#include "IRequest.hpp"

class Help// : public IRequest
{
public:
  typedef std::shared_ptr<AConnection> Owner;
public:
  Help(void);
  virtual ~Help(void);

  virtual std::string execute(Owner own, JSONReader &reader);
};
