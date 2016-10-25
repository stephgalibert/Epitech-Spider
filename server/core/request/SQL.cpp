//
// SQL.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 16:59:33 2016 stephane galibert
// Last update Tue Oct 25 17:08:28 2016 stephane galibert
//

#include "SQL.hpp"

SQL::SQL(void)
{
}

SQL::~SQL(void)
{
}

void SQL::execute(AConnection::shared own, JSONReader const& reader, Packet **reply)
{
  Params av;

  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ACCESS_DENIED);
    return ;
  }
  try {
    reader.getListValues("param", av);
    if (av.size() > 1) {
      *reply = StaticTools::CreatePacket(PacketType::PT_Response, own->executeSQL(av[1].second));
      return ;
    }
  } catch (std::exception const& e) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_JSON);
    return ;
  }
  *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER);
}
