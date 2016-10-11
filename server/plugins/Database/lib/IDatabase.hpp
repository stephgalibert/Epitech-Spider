//
// IDatabase.hpp for server in /home/galibe_s/project/SpiderServer/shared
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 15:03:02 2016 stephane galibert
// Last update Mon Aug 22 15:33:19 2016 stephane galibert
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
