//
// IRequest.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:53:12 2016 stephane galibert
// Last update Sat Nov  5 15:53:17 2016 stephane galibert
//

#pragma once

#include <memory>

#include <boost/noncopyable.hpp>
#include "Protocol.hpp"

#include "AConnection.hpp"

struct IRequest : private boost::noncopyable
{
  typedef std::shared_ptr<AConnection> Owner;
  virtual ~IRequest(void) {}

  virtual void execute(Owner own, std::string const& param, Packet **packet) = 0;
};
