//
// Set.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 08:46:16 2016 stephane galibert
// Last update Tue Oct 25 16:13:39 2016 stephane galibert
//

#include "Set.hpp"

Set::Set(void)
{
  _cmds["privilege"] = std::bind(&Set::privilege, this, std::placeholders::_1,
				 std::placeholders::_2);
}

Set::~Set(void)
{
}

//std::string Set::execute(AConnection::shared own, JSONReader &reader)
void Set::execute(AConnection::shared own, JSONReader const& reader,
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

Packet *Set::privilege(AConnection::shared own, Params const& av)
{
  ServerConfig const& sc = own->getServerConfig();

  if (av.size() > 3) {
    if (av[3].second != sc.getPassword()) {
      return (StaticTools::CreatePacket(PacketType::PT_Error, BAD_PWD));
      /*builder.addValue("type", "error");
      builder.addValue("name", "wrong password");
      return (builder.get());*/
    }
    else if (av[2].second == "admin") {
      own->setPrivilege(Privilege::PL_ADMIN);
      /*builder.addValue("type", "result");
      builder.addValue("data", "OK");
      return (builder.get());*/
      return (StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS));
    }
    else if (av[2].second == "user") {
      own->setPrivilege(Privilege::PL_USER);
      /*builder.addValue("type", "result");
      builder.addValue("data", "OK");
      return (builder.get());*/
      return (StaticTools::CreatePacket(PacketType::PT_Response, SUCCESS));
    }
  }

  return (StaticTools::CreatePacket(PacketType::PT_Error, BAD_PARAMETER));
}

/*std::string Set::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "set: bad parameter");
  return (builder.get());
  }*/
