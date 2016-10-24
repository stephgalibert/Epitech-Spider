//
// Reload.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 09:35:00 2016 stephane galibert
// Last update Wed Oct 19 16:20:10 2016 stephane galibert
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "IRequest.hpp"

class Reload// : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<std::string(AConnection::shared)> Cmds;
public:
  Reload(void);
  virtual ~Reload(void);

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  std::string plugin(AConnection::shared own);
  std::unordered_map<std::string, Cmds> _cmds;

  static std::string badParameter(void);
};
