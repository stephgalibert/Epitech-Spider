//
// PluginManager.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 03:15:39 2016 stephane galibert
// Last update Wed Aug 24 22:32:59 2016 stephane galibert
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
  std::unique_ptr<SoLoader> so(new SoLoader);
  void *info = NULL;
  void *data = NULL;

  try {
    so->setLibName(fname);
    so->load();

    info = so->sym("getPluginInfo");
    data = so->sym("registerPlugin");

    if (!retrievePluginInfo(info)) {
      return (false);
    }
    retrievePluginData(data, so);
  } catch (std::exception const& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return (false);
  }
  std::clog << "done" << std::endl;
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

bool PluginManager::retrievePluginInfo(void *handle)
{
  PluginInfo const& info = ((PluginInfo const& (*)(void))(handle))();
  if (!checkDuplicate(info.name)) {
    std::clog << "error: can not have duplicate plugin" << std::endl;
    return (false);
  }
  if (!checkPluginVersion(info.version)) {
    std::clog << "warning: the plugin version is not up to date ... " << std::flush;
  }
  _pluginsInfo.push_back(info);
  return (true);
}

bool PluginManager::retrievePluginData(void *handle, std::unique_ptr<SoLoader> &so)
{
  ((void (*)(std::unique_ptr<PluginRegister> &))(handle))(_pluginRegister);
  _plugins.push_back(std::move(so));
  return (true);
}

bool PluginManager::checkPluginVersion(size_t version) const
{
  return (version == _serverConfig.getVersion());
}

bool PluginManager::checkDuplicate(std::string const& name) const
{
  for (auto &it : _pluginsInfo) {
    if (it.name == name) {
      return (false);
    }
  }
  return (true);
}
