//
// Help.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 10:51:54 2016 stephane galibert
// Last update Tue Oct 25 16:54:01 2016 stephane galibert
//

#include "Help.hpp"

Help::Help(void)
{
}

Help::~Help(void)
{
}

void Help::execute(Owner own, JSONReader const& reader, Packet **reply)
{
  (void)own;
  (void)reader;

  std::ostringstream buf;
  boost::property_tree::ptree root;
  boost::property_tree::ptree nodeData;

  nodeData.put("cmd1", "descr1");
  nodeData.put("cmd2", "descr2");
  nodeData.put("cmd3", "descr3");
  root.add_child("data", nodeData);
  boost::property_tree::write_json(buf, root, false);

  *reply = StaticTools::CreatePacket(PacketType::PT_Response, buf.str());
}
