//
// Get.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 03:52:17 2016 stephane galibert
// Last update Wed Oct 19 15:30:01 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "IRequest.hpp"

class Get// : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<std::string(AConnection::shared)> Cmds;
public:
  Get(void);
  virtual ~Get(void);

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  std::string serverInfo(AConnection::shared own);
  std::unordered_map<std::string, Cmds> _cmds;

  static std::string badParameter(void);
};
