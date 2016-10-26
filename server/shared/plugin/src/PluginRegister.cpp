//
// PluginRegister.cpp for server in /home/galibe_s/project/SpiderServer/shared
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 08:06:26 2016 stephane galibert
// Last update Wed Oct 26 19:01:12 2016 stephane galibert
//

#include "PluginRegister.hpp"

PluginRegister::PluginRegister(void)
{
}

PluginRegister::~PluginRegister(void)
{
}

void PluginRegister::setUserInterface(std::string const& name,
				      std::unique_ptr<IUserInterface> ui)
{
  _ui.first = name;
  _ui.second.reset(ui.release());
}

std::unique_ptr<IUserInterface> const& PluginRegister::getUserInterface(void) const
{
  return (_ui.second);
}

std::unique_ptr<IUserInterface> &PluginRegister::getUserInterface(void)
{
  return (_ui.second);
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
  _ui.first = "";
  _ui.second.reset(NULL);
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
  /*else if (_ui.first == name) {
    if (_ui.second) {
      _ui.second->close();
    }
    _ui.second.reset(NULL);
    _ui.first = "";
    }*/
  return (false);
}
