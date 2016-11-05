//
// ICommand.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 14:15:34 2016 stephane galibert
// Last update Sat Nov  5 15:53:02 2016 stephane galibert
//

#pragma once

#include <memory>

#include <boost/noncopyable.hpp>
#include "Protocol.hpp"

#include "JSONReader.hpp"
#include "AConnection.hpp"

struct ICommand : private boost::noncopyable
{
  typedef std::shared_ptr<AConnection> Owner;
  virtual ~ICommand(void) {}

  virtual void execute(Owner own, JSONReader const& reader, Packet **packet) = 0;
};
