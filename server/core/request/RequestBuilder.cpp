//
// RequestBuilder.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Aug 18 16:07:24 2016 stephane galibert
// Last update Wed Oct 19 16:35:05 2016 stephane galibert
//

#include "RequestBuilder.hpp"

RequestBuilder::RequestBuilder(void)
{
  //_cmds["help"] = std::bind(&RequestBuilder::help, this);
  _cmds[(int)PacketType::PT_NewClient] = std::bind(&RequestBuilder::nc, this);
  _cmds[(int)PacketType::PT_KeyboardEvent] = std::bind(&RequestBuilder::key, this);
  _cmds[(int)PacketType::PT_MouseEvent] = std::bind(&RequestBuilder::key, this);
  _cmds[(int)PacketType::PT_Kill] = std::bind(&RequestBuilder::exit, this);
  /*_cmds["dump"] = std::bind(&RequestBuilder::dump, this);
  _cmds["reload"] = std::bind(&RequestBuilder::reload, this);
  _cmds["set"] = std::bind(&RequestBuilder::set, this);
  _cmds["get"] = std::bind(&RequestBuilder::get, this);
  _cmds["sql"] = std::bind(&RequestBuilder::sql, this);*/
}

RequestBuilder::~RequestBuilder(void)
{
}

std::unique_ptr<IRequest> RequestBuilder::create(PacketType type) const
{
  if (_cmds.find((int)type) != _cmds.cend()) {
    return (std::move(_cmds.at((int)type)()));
  }
  return (NULL);
}

/*std::unique_ptr<IRequest> RequestBuilder::help(void) const
{
  return (std::unique_ptr<IRequest>(new Help));
  }*/

std::unique_ptr<IRequest> RequestBuilder::nc(void) const
{
  return (std::unique_ptr<IRequest>(new Nc));
}

std::unique_ptr<IRequest> RequestBuilder::key(void) const
{
  return (std::unique_ptr<IRequest>(new Key));
}

std::unique_ptr<IRequest> RequestBuilder::exit(void) const
{
  return (std::unique_ptr<IRequest>(new Exit));
}

/*std::unique_ptr<IRequest> RequestBuilder::dump(void) const
{
  return (std::unique_ptr<IRequest>(new Dump));
}

std::unique_ptr<IRequest> RequestBuilder::reload(void) const
{
  return (std::unique_ptr<IRequest>(new Reload));
}

std::unique_ptr<IRequest> RequestBuilder::set(void) const
{
  return (std::unique_ptr<IRequest>(new Set));
}

std::unique_ptr<IRequest> RequestBuilder::get(void) const
{
  return (std::unique_ptr<IRequest>(new Get));
}

std::unique_ptr<IRequest> RequestBuilder::sql(void) const
{
  return (std::unique_ptr<IRequest>(new SQL));
  }*/
