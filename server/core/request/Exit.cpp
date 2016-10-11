//
// Exit.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:29:21 2016 stephane galibert
// Last update Thu Aug 18 14:27:34 2016 stephane galibert
//

#include "Exit.hpp"

Exit::Exit(void)
{
}

Exit::~Exit(void)
{
}

std::string Exit::execute(AConnection::shared own, JSONReader &reader)
{
  (void)reader;
  JSONBuilder builder;

  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    builder.addValue("type", "error");
    builder.addValue("name", "access denied");
    return (builder.get());
  }
  own->close();
  return ("");
}
