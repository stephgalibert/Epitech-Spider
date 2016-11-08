//
// Nc.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 17:50:00 2016 stephane galibert
// Last update Tue Nov  8 17:58:34 2016 stephane galibert
//

#include "Nc.hpp"

Nc::Nc(void)
{
}

Nc::~Nc(void)
{
}

void Nc::execute(AConnection::shared own, std::string const& param, Packet **reply)
{
  if (param.size() > 0) {
    own->setMacAddress(param);
    own->connectDB();
    *reply = StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS);
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_MAC);
  }
}
