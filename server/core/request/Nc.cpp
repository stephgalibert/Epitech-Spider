//
// Nc.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 19:29:03 2016 stephane galibert
// Last update Mon Nov  7 13:33:08 2016 stephane galibert
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
    own->connectToDB();
    *reply = StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS);
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_MAC);
  }
}
