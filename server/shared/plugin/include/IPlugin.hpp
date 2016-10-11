//
// IPlugin.hpp for server in /home/galibe_s/project/SpiderServer/shared
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug 19 15:11:21 2016 stephane galibert
// Last update Fri Aug 19 15:15:15 2016 stephane galibert
//

#pragma once

#include "PluginInfo.hpp"

struct IPlugin
{
  virtual ~IPlugin(void) {}
  virtual PluginInfo const& getPluginInfo(void) const = 0;
};
