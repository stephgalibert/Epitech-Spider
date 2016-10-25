//
// CommandBuilder.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 13:58:56 2016 stephane galibert
// Last update Tue Oct 25 17:16:46 2016 stephane galibert
//

#include "CommandBuilder.hpp"

CommandBuilder::CommandBuilder(void)
{
  _cmds["set"] = std::bind(&CommandBuilder::set, this);
  _cmds["dump"] = std::bind(&CommandBuilder::dump, this);
  _cmds["get"] = std::bind(&CommandBuilder::get, this);
  _cmds["help"] = std::bind(&CommandBuilder::help, this);
  _cmds["sql"] = std::bind(&CommandBuilder::sql, this);
  _cmds["reload"] = std::bind(&CommandBuilder::reload, this);
}

CommandBuilder::~CommandBuilder(void)
{
}

std::unique_ptr<ICommand> CommandBuilder::create(std::string const& name) const
{
  if (_cmds.find(name) != _cmds.cend()) {
    return (std::move(_cmds.at(name)()));
  }
  return (NULL);
}

std::unique_ptr<ICommand> CommandBuilder::set(void) const
{
  return (std::unique_ptr<ICommand>(new Set));
}

std::unique_ptr<ICommand> CommandBuilder::dump(void) const
{
  return (std::unique_ptr<ICommand>(new Dump));
}

std::unique_ptr<ICommand> CommandBuilder::get(void) const
{
  return (std::unique_ptr<ICommand>(new Get));
}

std::unique_ptr<ICommand> CommandBuilder::help(void) const
{
  return (std::unique_ptr<ICommand>(new Help));
}

std::unique_ptr<ICommand> CommandBuilder::sql(void) const
{
  return (std::unique_ptr<ICommand>(new SQL));
}


std::unique_ptr<ICommand> CommandBuilder::reload(void) const
{
  return (std::unique_ptr<ICommand>(new Reload));
}
