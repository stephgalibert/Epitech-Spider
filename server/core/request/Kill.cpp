//
// Kill.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Nov 10 11:44:54 2016 stephane galibert
// Last update Thu Nov 10 12:03:20 2016 stephane galibert
//

#include "Kill.hpp"

Kill::Kill(void)
{
}

Kill::~Kill(void)
{
}

void Kill::execute(AConnection::shared own, std::string const& param, Packet **reply)
{
  if (!own->kill(param)) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_MAC);
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS);
  }
}
