//
// UnixDlLoader.hpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 19:42:18 2016 stephane galibert
// Last update Wed Oct 26 14:59:14 2016 stephane galibert
//

#pragma once

#include <string>
#include <stdexcept>

#include <dlfcn.h>

#include "ADlLoader.hpp"

class UnixDlLoader : public ADlLoader
{
public:
  UnixDlLoader(void);
  virtual ~UnixDlLoader(void);

  virtual void setLibName(std::string const& name);
  virtual void load(void);

  virtual void registerInstance(std::unique_ptr<PluginRegister> &pr,
				PluginInfo &pluginInfo,
				std::vector<PluginInfo> const& loaded,
				size_t version);
private:
  void *sym(std::string const& symbol);
  void retrievePluginInfo(void *handle, PluginInfo &info,
			  std::vector<PluginInfo> const& loaded, size_t version);
  void retrievePluginData(void *handle, std::unique_ptr<PluginRegister> &pr);
  bool checkDuplicate(std::vector<PluginInfo> const& loaded,
		      std::string const& name);

  void *_ld;
};
