//
// Set.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:40:19 2016 stephane galibert
// Last update Thu Aug 18 14:29:55 2016 stephane galibert
//

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "IRequest.hpp"
#include "Privilege.hpp"

class Set : public IRequest
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<std::string(AConnection::shared, Params const&)> Cmds;
public:
  Set(void);
  virtual ~Set(void);

  virtual std::string execute(AConnection::shared own, JSONReader &reader);
private:
  std::string privilege(AConnection::shared own, Params const& av);
  std::unordered_map<std::string, Cmds> _cmds;

  static std::string badParameter(void);
};
