//
// PluginLoader.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 19:04:50 2016 stephane galibert
// Last update Fri Aug 12 00:07:17 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <iterator>

#include <boost/filesystem.hpp>

class PluginLoader
{
public:
  PluginLoader(void);
  ~PluginLoader(void);

  void parseDirectory(std::string const& dir);
  std::vector<std::string> const& getPlugins(void) const;

private:
  std::vector<std::string> _plugins;
};
