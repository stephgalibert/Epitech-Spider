//
// PluginRegister.cpp for server in /home/galibe_s/project/SpiderServer/shared
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 08:06:26 2016 stephane galibert
// Last update Mon Aug 22 15:49:10 2016 stephane galibert
//

#include "PluginRegister.hpp"

PluginRegister::PluginRegister(void)
{
}

PluginRegister::~PluginRegister(void)
{
}

void PluginRegister::setUserInterface(std::unique_ptr<IUserInterface> ui)
{
  _ui.reset(ui.release());
}

std::unique_ptr<IUserInterface> const& PluginRegister::getUserInterface(void) const
{
  return (_ui);
}

std::unique_ptr<IUserInterface> &PluginRegister::getUserInterface(void)
{
  return (_ui);
}

void PluginRegister::setDatabase(std::unique_ptr<IDatabase> db)
{
  _db.reset(db.release());
}

std::unique_ptr<IDatabase> const& PluginRegister::getDatabase(void) const
{
  return (_db);
}

std::unique_ptr<IDatabase> &PluginRegister::getDatabase(void)
{
  return (_db);
}

void PluginRegister::clear(void)
{
  _ui.reset(NULL);
  _db.reset(NULL);
}
