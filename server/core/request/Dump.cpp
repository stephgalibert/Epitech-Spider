//
// Dump.cpp for dump in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:51:37 2016 stephane galibert
// Last update Sat Nov  5 15:51:37 2016 stephane galibert
//

#include "Dump.hpp"

Dump::Dump(void)
{
  _cmds["plugin"] = std::bind(&Dump::plugin, this, std::placeholders::_1);
}

Dump::~Dump(void)
{
}

void Dump::execute(AConnection::shared own, JSONReader const& reader,
		   Packet **reply)
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

Packet *Dump::plugin(AConnection::shared own)
{
  std::ostringstream buf;
  boost::property_tree::ptree root;
  boost::property_tree::ptree nodeData, nodeObject;
  std::vector<PluginInfo> const& info = own->getPluginsInfo();

  for (auto &it : info)
    {
      nodeData.put("name", it.name);
      nodeData.put("author", it.author);
      nodeData.put("version", it.version);
      nodeObject.push_back(std::make_pair(it.name, nodeData));
    }
  root.put_child("data", nodeObject);
  boost::property_tree::write_json(buf, root, false);
  return (StaticTools::CreatePacket(PacketType::PT_Response, buf.str()));
}
