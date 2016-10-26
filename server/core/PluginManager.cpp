//
// PluginManager.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 03:15:39 2016 stephane galibert
// Last update Wed Oct 26 15:45:57 2016 stephane galibert
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

    dl->registerInstance(_pluginRegister, info, _pluginsInfo,
			 _serverConfig.getVersion());
    _pluginsInfo.push_back(info);
    _plugins.push_back(std::move(dl));

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return (false);
  }

  std::cerr << "done" << std::endl;
  return (true);
}

void PluginManager::close(std::string const& pluginName)
{
  (void)pluginName;
  // getUIS()->it->close();
  // it = it(_pluginsInfo).erase(it);
  // it = it(_plugins).erase(it);

}

std::vector<PluginInfo> const& PluginManager::getPluginsInfo(void) const
{
  return (_pluginsInfo);
}

void PluginManager::closeAll(void)
{
  closeUserInterface();
  closeDatabase();
  _pluginRegister->clear();
  _pluginsInfo.clear();
  _plugins.clear();
}

void PluginManager::startUserInterface(void)
{
  std::unique_ptr<IUserInterface> const& ptr = _pluginRegister->getUserInterface();
  if (ptr) {
    ptr->start();
  }
}

void PluginManager::closeUserInterface(void)
{
  std::unique_ptr<IUserInterface> const& ptr = _pluginRegister->getUserInterface();
  if (ptr) {
    ptr->close();
  }
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
