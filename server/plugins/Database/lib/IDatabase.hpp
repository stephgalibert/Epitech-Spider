//
// IDatabase.hpp for plugin in /home/galibe_s/rendu/Spider/server/shared/plugin/include
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov 12 19:55:28 2016 stephane galibert
// Last update Sat Nov 12 19:55:29 2016 stephane galibert
//

#pragma once

#include "IPlugin.hpp"

struct IDatabase : public IPlugin
{
  virtual ~IDatabase(void) {}
  virtual PluginInfo const& getPluginInfo(void) const = 0;
  virtual void init(void) = 0;
  virtual void close(void) = 0;
  virtual void newConnection(std::string const& id) = 0;
  virtual void lostConnection(std::string const& id) = 0;
  virtual void newKey(std::string const& id, std::string const& key) = 0;
  virtual std::string executeStatement(std::string const& stmt) = 0;
};
