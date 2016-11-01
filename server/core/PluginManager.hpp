//
// PluginManager.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 03:08:32 2016 stephane galibert
// Last update Tue Nov  1 20:16:27 2016 stephane galibert
//

#pragma once

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>

#include "IDatabase.hpp"

#include "ServerConfig.hpp"
#include "PluginInfo.hpp"
#include "UnixDlLoader.hpp"
#include "PluginRegister.hpp"

class PluginManager
{
public:
  PluginManager(ServerConfig const& serverConfig);
  ~PluginManager(void);

  bool load(std::string const& fname);
  bool close(std::string const& pluginName);
  std::vector<PluginInfo> const getPluginsInfo(void) const;
  void closeAll(void);

  void initDatabase(void);
  void closeDatabase(void);
  void newConnectionDatabase(std::string const& id);
  void lostConnectionDatabase(std::string const& id);
  std::string executeSQLDatabase(std::string const& stmt);
  void newKeyDatabase(std::string const& id, std::string const& key);

private:
  ServerConfig const& _serverConfig;
  std::list<std::pair<PluginInfo, std::unique_ptr<UnixDlLoader> > > _plugins;
  std::unique_ptr<PluginRegister> _pluginRegister;
};
