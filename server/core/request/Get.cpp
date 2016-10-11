//
// Get.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 03:54:23 2016 stephane galibert
// Last update Thu Aug 18 14:28:07 2016 stephane galibert
//

#include "Get.hpp"

Get::Get(void)
{
  _cmds["serverinfo"] = std::bind(&Get::serverInfo, this, std::placeholders::_1);
}

Get::~Get(void)
{
}

std::string Get::execute(AConnection::shared own, JSONReader &reader)
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
  return (Get::badParameter());
}

std::string Get::serverInfo(AConnection::shared own)
{
  JSONBuilder builder;
  std::vector<std::pair<std::string, std::string> > av;
  ServerConfig const& sc = own->getServerConfig();

  av.push_back(std::make_pair("version", std::to_string(sc.getVersion())));
  av.push_back(std::make_pair("pwd", sc.getPassword()));

  builder.addValue("type", "result");
  builder.addListValues("data", av);
  return (builder.get());
}

std::string Get::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "get: bad parameter");
  return (builder.get());
}
