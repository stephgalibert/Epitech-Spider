//
// PluginLoader.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 19:08:20 2016 stephane galibert
// Last update Wed Aug 10 23:17:06 2016 stephane galibert
//

#include "PluginLoader.hpp"

PluginLoader::PluginLoader(void)
{
}

PluginLoader::~PluginLoader(void)
{
}

void PluginLoader::parseDirectory(std::string const& dir)
{
  std::vector<boost::filesystem::directory_entry> entry;
  boost::filesystem::path p(dir);

  try {
    std::copy(boost::filesystem::directory_iterator(p),
	      boost::filesystem::directory_iterator(),
	      std::back_inserter(entry));

    for (auto it : entry) {
      if (it.path().extension() == ".so")
	_plugins.push_back(it.path().string());
    }
  } catch (std::exception const& e) {
    std::cerr << "PluginLoader::parseDirectory - " << e.what() << std::endl;
  }
}

std::vector<std::string> const& PluginLoader::getPlugins(void) const
{
  return (_plugins);
}
