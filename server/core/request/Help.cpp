//
// Help.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 10:51:54 2016 stephane galibert
// Last update Tue Aug 16 11:14:54 2016 stephane galibert
//

#include "Help.hpp"

Help::Help(void)
{
}

Help::~Help(void)
{
}

std::string Help::execute(Owner own, JSONReader &reader)
{
  (void)own;
  (void)reader;

  std::ostringstream buf;
  boost::property_tree::ptree root;
  boost::property_tree::ptree nodeData;

  root.put("type", "result");
  nodeData.put("cmd1", "descr1");
  nodeData.put("cmd2", "descr2");
  nodeData.put("cmd3", "descr3");
  root.add_child("data", nodeData);
  boost::property_tree::write_json(buf, root, false);
  return (buf.str());

  /*Params av;
  try {
    reader.getListValues("param", av);
    if (av.size() > 1) {
      if (_cmds.find(av[1]) != _cmds.cend())
	return (_cmds.at(av[1])(own));
    }
  } catch (std::exception const& e) {
    throw (e);
  }
  return (Help::badParameter());
  return ("");*/
}
