//
// Reload.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 09:36:22 2016 stephane galibert
// Last update Sun Aug 21 22:06:19 2016 stephane galibert
//

#include "Reload.hpp"

Reload::Reload(void)
{
  _cmds["plugin"] = std::bind(&Reload::plugin, this, std::placeholders::_1);
}

Reload::~Reload(void)
{
}

std::string Reload::execute(AConnection::shared own, JSONReader &reader)
{
  Params av;

  try {
    reader.getListValues("param", av);
    if (av.size() > 1) {
      if (_cmds.find(av[1].second) != _cmds.cend())
	return (_cmds.at(av[1].second)(own));
    }
  } catch (std::exception const& e) {
    throw (e);
  }
  return (Reload::badParameter());
}

std::string Reload::plugin(AConnection::shared own)
{
  JSONBuilder builder;

  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    builder.addValue("type", "error");
    builder.addValue("name", "access denied");
    return (builder.get());
  }

  builder.addValue("type", "result");
  builder.addValue("data", "OK");
  own->write(builder.get());
  own->reloadPlugin();
  return ("");
}

std::string Reload::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "reload: bad parameter");
  return (builder.get());
}
