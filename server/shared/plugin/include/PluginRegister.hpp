//
// PluginRegister.hpp for server in /home/galibe_s/project/SpiderServer/shared
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 08:02:14 2016 stephane galibert
// Last update Tue Nov  1 20:15:18 2016 stephane galibert
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
