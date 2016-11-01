//
// ADlLoader.hpp for server in /home/galibe_s/rendu/Spider/server/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Oct 26 14:54:41 2016 stephane galibert
// Last update Wed Oct 26 14:59:37 2016 stephane galibert
//

#pragma once

#include <vector>
#include <memory>

#include "PluginRegister.hpp"
#include "PluginInfo.hpp"

class ADlLoader
{
public:
  ADlLoader(void);
  virtual ~ADlLoader(void);

  virtual void setLibName(std::string const& name) = 0;
  virtual void load(void) = 0;
  virtual void registerInstance(std::unique_ptr<PluginRegister> &pr,
				PluginInfo &pluginInfo,
				std::vector<PluginInfo> const& loaded,
				size_t version) = 0;
protected:
  std::string _name;
};
