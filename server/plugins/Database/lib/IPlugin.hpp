//
// IPlugin.hpp for plugin in /home/galibe_s/rendu/Spider/server/shared/plugin/include
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov 12 19:55:40 2016 stephane galibert
// Last update Sat Nov 12 19:55:42 2016 stephane galibert
//

#pragma once

#include "PluginInfo.hpp"

struct IPlugin
{
  virtual ~IPlugin(void) {}
  virtual PluginInfo const& getPluginInfo(void) const = 0;
};
