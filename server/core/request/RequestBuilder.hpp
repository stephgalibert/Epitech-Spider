//
// RequestBuilder.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Aug 18 13:24:38 2016 stephane galibert
// Last update Wed Oct 19 16:34:35 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/noncopyable.hpp>

#include "Protocol.hpp"
#include "IRequest.hpp"
//#include "Help.hpp"
#include "Nc.hpp"
#include "Exit.hpp"
/*#include "Dump.hpp"
#include "Reload.hpp"
#include "Set.hpp"
#include "Get.hpp"
#include "SQL.hpp"*/
#include "Key.hpp"

class RequestBuilder : private boost::noncopyable
{
public:
  typedef std::function<std::unique_ptr<IRequest>(void)> Cmds;
public:
  RequestBuilder(void);
  ~RequestBuilder(void);

  std::unique_ptr<IRequest> create(PacketType type) const;
private:
  //std::unique_ptr<IRequest> help(void) const;
  std::unique_ptr<IRequest> nc(void) const;
  std::unique_ptr<IRequest> key(void) const;
  std::unique_ptr<IRequest> exit(void) const;
  //std::unique_ptr<IRequest> dump(void) const;
  //std::unique_ptr<IRequest> reload(void) const;
  //std::unique_ptr<IRequest> set(void) const;
  //std::unique_ptr<IRequest> get(void) const;
  //std::unique_ptr<IRequest> sql(void) const;

  std::unordered_map<int, Cmds> _cmds;
};
