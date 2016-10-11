//
// IRequest.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 07:54:41 2016 stephane galibert
// Last update Tue Oct  4 21:15:33 2016 stephane galibert
//

#pragma once

#include <memory>

#include <boost/noncopyable.hpp>

#include "JSONBuilder.hpp"
#include "JSONReader.hpp"

#include "AConnection.hpp"

struct IRequest : private boost::noncopyable
{
  typedef std::shared_ptr<AConnection> Owner;
  virtual ~IRequest(void) {}
  virtual std::string execute(Owner own, JSONReader &reader) = 0;
};
