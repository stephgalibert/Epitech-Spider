//
// PluginRegister.hpp for server in /home/galibe_s/rendu/Spider/server/shared/plugin/include
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov 12 19:56:05 2016 stephane galibert
// Last update Sat Nov 12 19:56:05 2016 stephane galibert
//

#pragma once

#include <memory>
#include <utility>

#include "IDatabase.hpp"

#include <boost/noncopyable.hpp>

class PluginRegister : private boost::noncopyable
{
public:
  PluginRegister(void);
  ~PluginRegister(void);

  void setDatabase(std::string const& name, std::unique_ptr<IDatabase> db);
  std::unique_ptr<IDatabase> const& getDatabase(void) const;
  std::unique_ptr<IDatabase> &getDatabase(void);

  void clear(void);
  bool unregisterPlugin(std::string const& name);
private:
  std::pair<std::string, std::unique_ptr<IDatabase> > _db;
};
