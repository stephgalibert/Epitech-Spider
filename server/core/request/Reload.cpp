//
// Reload.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:54:43 2016 stephane galibert
// Last update Sat Nov  5 15:54:44 2016 stephane galibert
//

#include "Reload.hpp"

Reload::Reload(void)
{
  _cmds["plugin"] = std::bind(&Reload::plugin, this, std::placeholders::_1);
}

Reload::~Reload(void)
{
}

void Reload::execute(AConnection::shared own, JSONReader const& reader,
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

Packet *Reload::plugin(AConnection::shared own)
{
  if (own->getPrivilege() != Privilege::PL_ADMIN) {
    return (StaticTools::CreatePacket(PacketType::PT_Error, ACCESS_DENIED));
  }

  own->write(StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS));
  own->reloadPlugin();
  return (NULL);
}
