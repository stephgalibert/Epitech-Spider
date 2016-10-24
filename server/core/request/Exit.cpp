//
// Exit.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:29:21 2016 stephane galibert
// Last update Mon Oct 24 11:23:37 2016 stephane galibert
//

#include "Exit.hpp"

Exit::Exit(void)
{
}

Exit::~Exit(void)
{
}

//std::string Exit::execute(AConnection::shared own, JSONReader &reader)
void Exit::execute(AConnection::shared own, std::string const& param, Packet **reply)
{
  /*(void)reader;
    JSONBuilder builder;

  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    builder.addValue("type", "error");
    builder.addValue("name", "access denied");
    return (builder.get());
    }*/
  (void)param;
  (void)reply;
  own->close();
  //return ("");
}
