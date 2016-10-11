//
// Configuration.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 08:23:03 2016 stephane galibert
// Last update Tue Aug 16 08:45:25 2016 stephane galibert
//

#include "Configuration.hpp"

Configuration::Configuration(std::string const& rootName)
{
  _rootName = rootName;
}

Configuration::~Configuration(void)
{
}

void Configuration::read(std::string const& filename)
{
  try {
    _reader.readFromFile(filename);
  } catch (std::exception const& e) {
    throw (e);
  }
}
