//
// Exit.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:29:21 2016 stephane galibert
// Last update Wed Oct 26 17:07:14 2016 stephane galibert
//

#include "Exit.hpp"

Exit::Exit(void)
{
}

Exit::~Exit(void)
{
}

void Exit::execute(AConnection::shared own, std::string const& param, Packet **reply)
{
  (void)param;
  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ACCESS_DENIED);
  }
  else {
    own->close();
  }
}
