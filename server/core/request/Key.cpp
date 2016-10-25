//
// Key.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 24 22:25:18 2016 stephane galibert
// Last update Wed Oct 19 16:18:57 2016 stephane galibert
//

#include "Key.hpp"

Key::Key(void)
{
}

Key::~Key(void)
{
}

//std::string Key::execute(AConnection::shared own, JSONReader &reader)
void Key::execute(AConnection::shared own, std::string const& param,
		  Packet **packet)
{
  /* std::string param;

  try {
    param = reader.getValue<std::string>("param");
    JSONBuilder builder;
    own->addLog(param);
    builder.addValue("type", "result");
    builder.addValue("data", "OK");
    return (builder.get());
  } catch (std::exception const& e) {
  throw (e);
  }
  return (Key::badParameter());*/
  (void)packet;
  own->addLog(param);
}

/*std::string Key::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "Key: bad parameter");
  return (builder.get());
  }*/
