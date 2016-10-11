//
// JSONBuilder.cpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 16:54:20 2016 stephane galibert
// Last update Wed Aug 17 05:24:34 2016 stephane galibert
//

#include "JSONBuilder.hpp"

JSONBuilder::JSONBuilder(void)
{
}

JSONBuilder::~JSONBuilder(void)
{
}

void JSONBuilder::read(std::string const& json)
{
  try {
    std::istringstream is(json);
    boost::property_tree::read_json(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}

std::string JSONBuilder::get(void)
{
  std::ostringstream buf;
  boost::property_tree::write_json(buf, _root, false);
  return (buf.str());
}
