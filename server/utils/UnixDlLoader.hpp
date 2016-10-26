//
// UnixDlLoader.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 19:42:18 2016 stephane galibert
// Last update Wed Oct 26 14:45:44 2016 stephane galibert
//

#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include <dlfcn.h>

#include "PluginRegister.hpp"
#include "PluginInfo.hpp"

class UnixDlLoader
{
public:
  UnixDlLoader(void);
  ~UnixDlLoader(void);

  void setLibName(std::string const& name);
  void load(void);

  void registerInstance(std::unique_ptr<PluginRegister> &pr, PluginInfo &pluginInfo,
			std::vector<PluginInfo> const& loaded, size_t version);
private:
  void *sym(std::string const& symbol);
  void retrievePluginInfo(void *handle, PluginInfo &info,
			  std::vector<PluginInfo> const& loaded, size_t version);
  void retrievePluginData(void *handle, std::unique_ptr<PluginRegister> &pr);
  bool checkDuplicate(std::vector<PluginInfo> const& loaded,
		      std::string const& name);

  void *_ld;
  std::string _name;
};
