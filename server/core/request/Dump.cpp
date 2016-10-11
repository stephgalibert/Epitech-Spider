//
// Dump.cpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug 14 07:32:16 2016 stephane galibert
// Last update Sun Aug 21 22:23:53 2016 stephane galibert
//

#include "Dump.hpp"

Dump::Dump(void)
{
  _cmds["plugin"] = std::bind(&Dump::plugin, this, std::placeholders::_1);
}

Dump::~Dump(void)
{
}

std::string Dump::execute(AConnection::shared own, JSONReader &reader)
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
  return (Dump::badParameter());
}

std::string Dump::plugin(AConnection::shared own)
{
  std::ostringstream buf;
  boost::property_tree::ptree root;
  boost::property_tree::ptree nodeData, nodeObject;
  std::vector<PluginInfo> const& info = own->getPluginsInfo();

  root.put("type", "result");
  for (auto &it : info)
    {
      nodeData.put("name", it.name);
      nodeData.put("author", it.author);
      nodeData.put("version", it.version);
      nodeObject.push_back(std::make_pair(it.name, nodeData));
    }
  root.put_child("data", nodeObject);
  boost::property_tree::write_json(buf, root, false);
  return (buf.str());
}

std::string Dump::badParameter(void)
{
  JSONBuilder builder;

  builder.addValue("type", "error");
  builder.addValue("name", "dump: bad parameter");
  return (builder.get());
}
