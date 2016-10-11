//
// IUserInterface.hpp for server in /home/galibe_s/project/SpiderServer/ui
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Aug  8 20:23:00 2016 stephane galibert
// Last update Fri Aug 19 15:14:42 2016 stephane galibert
//

#pragma once

#include "IPlugin.hpp"

class IUserInterface : public IPlugin
{
public:
  virtual ~IUserInterface(void) {}
  virtual void start(void) = 0;
  virtual void close(void) = 0;
  virtual PluginInfo const& getPluginInfo(void) const = 0;
};
