//
// Get.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 03:54:23 2016 stephane galibert
// Last update Tue Oct 25 17:16:06 2016 stephane galibert
//

#include "Get.hpp"

Get::Get(void)
{
  _cmds["serverinfo"] = std::bind(&Get::serverInfo, this, std::placeholders::_1);
}

Get::~Get(void)
{
}

void Get::execute(AConnection::shared own, JSONReader const& reader, Packet **reply)
{
  Params av;

  try {
    reader.getListValues("param", av);
    if (av.size() > 1) {
      if (_cmds.find(av[1].second) != _cmds.cend()) {
	*reply = _cmds.at(av[1].second)(own);
	return ;
      }
    }
  } catch (std::exception const& e) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_JSON);
    return ;
  }
  *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER);
}

Packet *Get::serverInfo(AConnection::shared own)
{
  JSONBuilder builder;
  std::vector<std::pair<std::string, std::string> > av;
  ServerConfig const& sc = own->getServerConfig();

  av.push_back(std::make_pair("version", std::to_string(sc.getVersion())));
  av.push_back(std::make_pair("pwd", sc.getPassword()));

  builder.addListValues("data", av);

  return (StaticTools::CreatePacket(PacketType::PT_Response, builder.get()));
}
