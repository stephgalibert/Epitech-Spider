//
// PluginManager.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 03:15:39 2016 stephane galibert
// Last update Tue Nov  1 20:17:54 2016 stephane galibert
//

#include "PluginManager.hpp"

PluginManager::PluginManager(ServerConfig const& serverConfig)
  : _serverConfig(serverConfig)
{
  _pluginRegister.reset(new PluginRegister);
}

PluginManager::~PluginManager(void)
{
}

bool PluginManager::load(std::string const& fname)
{
  std::clog << "loading plugin '" << fname << "' ... " << std::flush;
  std::unique_ptr<UnixDlLoader> dl(new UnixDlLoader);
  PluginInfo info;

  try {
    dl->setLibName(fname);
    dl->load();

    dl->registerInstance(_pluginRegister, info, getPluginsInfo(),
			 _serverConfig.getVersion());
    _plugins.emplace_back(info, std::move(dl));

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return (false);
  }

  std::cerr << "done" << std::endl;
  return (true);
}

bool PluginManager::close(std::string const& pluginName)
{
  std::list<std::pair<PluginInfo, std::unique_ptr<UnixDlLoader> > >::iterator it;
  it = _plugins.begin();
  while (it != _plugins.end() && it->first.name != pluginName) {
    ++it;
  }
  if (it != _plugins.end() && it->first.name == pluginName) {
    if (_pluginRegister->unregisterPlugin(pluginName)) {
      _plugins.erase(it);
      return (true);
    }
  }
  return (false);
}

std::vector<PluginInfo> const PluginManager::getPluginsInfo(void) const
{
  std::vector<PluginInfo> infos;
  for (auto &it : _plugins) {
    infos.push_back(it.first);
  }
  return (infos);
}

void PluginManager::closeAll(void)
{
  closeDatabase();
  _pluginRegister->clear();
  _plugins.erase(_plugins.begin(), _plugins.end());
}

void PluginManager::closeDatabase(void)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    ptr->close();
  }
}

void PluginManager::initDatabase(void)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    ptr->init();
  }
}

void PluginManager::newConnectionDatabase(std::string const& id)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    ptr->newConnection(id);
  }
}

void PluginManager::lostConnectionDatabase(std::string const& id)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    ptr->lostConnection(id);
  }
}

std::string PluginManager::executeSQLDatabase(std::string const& stmt)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    return (ptr->executeStatement(stmt));
  }
  return ("");
}

void PluginManager::newKeyDatabase(std::string const& id, std::string const& key)
{
  std::unique_ptr<IDatabase> const& ptr = _pluginRegister->getDatabase();
  if (ptr) {
    ptr->newKey(id, key);
  }
}
