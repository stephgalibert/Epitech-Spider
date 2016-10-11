//
// SQL.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 21 22:04:39 2016 stephane galibert
// Last update Sun Aug 21 22:08:50 2016 stephane galibert
//

#include "SQL.hpp"

SQL::SQL(void)
{
}

SQL::~SQL(void)
{
}

std::string SQL::execute(AConnection::shared own, JSONReader &reader)
{
  JSONBuilder builder;
  Params av;

  try {
    if (own->getPrivilege() != Privilege::PL_ADMIN) {
      builder.addValue("type", "error");
      builder.addValue("name", "access denied");
      return (builder.get());
    }
    reader.getListValues("param", av);
    if (av.size() > 1) {
      return (own->executeSQL(av[1].second));
    }
  } catch (std::exception const& e) {
    throw (e);
  }
  return (SQL::badParameter());
}

std::string SQL::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "SQL: bad parameter");
  return (builder.get());
}
