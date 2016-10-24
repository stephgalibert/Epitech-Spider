//
// Nc.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 19:29:03 2016 stephane galibert
// Last update Wed Oct 19 17:09:21 2016 stephane galibert
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
  (void)reply;
  if (param.size() == 12) {
    own->setMacAddress(param);
    own->connectToDB();
  }
}

/*std::string Nc::execute(AConnection::shared own, JSONReader &reader)
{
  Params av;

  try {
    reader.getListValues("param", av);
    if (av.size() > 1 && av[1].second.size() == 12) {
      JSONBuilder builder;
      own->setMacAddress(av[1].second);
      own->connectToDB();
      builder.addValue("type", "result");
      builder.addValue("data", "OK");
      return (builder.get());
    }
  } catch (std::exception const& e) {
    throw (e);
  }
  return (Nc::badParameter());
}

std::string Nc::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "Nc: bad parameter");
  return (builder.get());
  }*/
