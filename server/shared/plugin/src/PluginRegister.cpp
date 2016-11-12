//
// PluginRegister.cpp for server in /home/galibe_s/rendu/Spider/server/shared/plugin/src
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov 12 19:56:17 2016 stephane galibert
// Last update Sat Nov 12 19:56:18 2016 stephane galibert
//

#include "PluginRegister.hpp"

PluginRegister::PluginRegister(void)
{
}

PluginRegister::~PluginRegister(void)
{
}

void PluginRegister::setDatabase(std::string const& name,
				 std::unique_ptr<IDatabase> db)
{
  _db.first = name;
  _db.second.reset(db.release());
}

std::unique_ptr<IDatabase> const& PluginRegister::getDatabase(void) const
{
  return (_db.second);
}

std::unique_ptr<IDatabase> &PluginRegister::getDatabase(void)
{
  return (_db.second);
}

void PluginRegister::clear(void)
{
  _db.first = "";
  _db.second.reset(NULL);
}

bool PluginRegister::unregisterPlugin(std::string const& name)
{
  if (_db.first == name) {
    if (_db.second) {
      _db.second->close();
    }
    _db.second.reset(NULL);
    _db.first = "";
    return (true);
  }
  return (false);
}
