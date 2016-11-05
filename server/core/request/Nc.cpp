//
// Nc.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 19:29:03 2016 stephane galibert
// Last update Sat Nov  5 16:05:33 2016 stephane galibert
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
  if (param.size() == 12) {
    own->setMacAddress(param);
    own->connectToDB();
    *reply = StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS);
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_MAC);
  }
}
