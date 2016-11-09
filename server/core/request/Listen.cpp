//
// Listen.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Nov  9 03:52:03 2016 stephane galibert
// Last update Wed Nov  9 04:37:46 2016 stephane galibert
//

#include "Listen.hpp"

Listen::Listen(void)
{
}

Listen::~Listen(void)
{
}

void Listen::execute(AConnection::shared own, JSONReader const& reader, Packet **reply)
{
  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ACCESS_DENIED);
    return ;
  }
  try {
    std::string mac = reader.getValue<std::string>("param");
    std::string enable = reader.getValue<std::string>("enable");
    if (mac.size() > 0 && enable.size() > 0) {
      own->listen(mac, enable == "true");
      *reply = StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS);
      return ;
    }
  } catch (std::exception const& e) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_JSON);
    return ;
  }
  *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER);
}
