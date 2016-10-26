//
// UnixDlLoader.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Oct 26 13:56:52 2016 stephane galibert
// Last update Wed Oct 26 14:50:22 2016 stephane galibert
//

#include "UnixDlLoader.hpp"

UnixDlLoader::UnixDlLoader(void)
  : _ld(NULL)
{
}

UnixDlLoader::~UnixDlLoader(void)
{
  if (_ld) {
    dlclose(_ld);
  }
}

void UnixDlLoader::setLibName(std::string const& lib)
{
  if (_ld) {
    dlclose(_ld);
  }
  _name = lib;
}

void UnixDlLoader::load(void)
{
  _ld = dlopen(_name.c_str(), RTLD_NOW);
  if (!_ld) {
    throw (std::runtime_error(dlerror()));
  }
}

void UnixDlLoader::registerInstance(std::unique_ptr<PluginRegister> &pr,
				    PluginInfo &pluginInfo,
				    std::vector<PluginInfo> const& loaded,
				    size_t version)
{
  void *data = NULL;
  void *info = NULL;

  try {
    data = sym("registerPlugin");
    info = sym("getPluginInfo");

    retrievePluginInfo(info, pluginInfo, loaded, version);
    retrievePluginData(data, pr);

  } catch (std::exception const& e) {
    throw (e);
  }
}

void *UnixDlLoader::sym(std::string const& symbol)
{
  void *sym = NULL;
  char *error = NULL;

  dlerror();
  if (_ld) {
    sym = dlsym(_ld, symbol.c_str());
    error = dlerror();
    if (error) {
      throw (std::runtime_error(error));
    }
  }
  return (sym);
}

void UnixDlLoader::retrievePluginInfo(void *handle,
				      PluginInfo &info,
				      std::vector<PluginInfo> const& loaded,
				      size_t version)
{
  PluginInfo const& tmp = ((PluginInfo const& (*)(void))(handle))();
  if (!checkDuplicate(loaded, tmp.name)) {
    throw (std::runtime_error("Error: Can not have duplicate plugin"));
  }
  if (tmp.version != version) {
    throw (std::runtime_error("Error: the plugin is not up-to-date, please contact the plugin's creator"));
  }
  info.author = tmp.author;
  info.name = tmp.name;
  info.version = tmp.version;
}

void UnixDlLoader::retrievePluginData(void *handle,
				      std::unique_ptr<PluginRegister> &pr)
{
  ((void (*)(std::unique_ptr<PluginRegister> &))(handle))(pr);
}

bool UnixDlLoader::checkDuplicate(std::vector<PluginInfo> const& loaded,
				  std::string const& name)
{
  for (auto &it : loaded) {
    if (it.name == name) {
      return (false);
    }
  }
  return (true);
}
