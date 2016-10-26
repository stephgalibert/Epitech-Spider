//
// Close.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Oct 26 15:16:58 2016 stephane galibert
// Last update Wed Oct 26 15:40:13 2016 stephane galibert
//

#include "Close.hpp"

Close::Close(void)
{
  _cmds["plugin"] = std::bind(&Close::plugin, this, std::placeholders::_1,
			      std::placeholders::_2);
}

Close::~Close(void)
{
}

void Close::execute(AConnection::shared own, JSONReader const& reader,
		    Packet **reply)
{
  Params av;

  try {
    reader.getListValues("param", av);
    if (av.size() > 1) {
      if (_cmds.find(av[1].second) != _cmds.cend()) {
	*reply = _cmds.at(av[1].second)(own, av);
	return ;
      }
    }
  } catch (std::exception const& e) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_JSON);
    return ;
  }
  *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER);
}

Packet *Close::plugin(AConnection::shared own, Params const& av)
{
  if (av.size() > 2) {
    own->closePlugin(av[2].second);
    return (NULL);
  }
  return (StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER));
}
