//
// CommandBuilder.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 25 13:54:32 2016 stephane galibert
// Last update Wed Oct 26 15:28:01 2016 stephane galibert
//

#pragma once

#include <boost/noncopyable.hpp>

#include "ICommand.hpp"
#include "Set.hpp"
#include "Dump.hpp"
#include "Get.hpp"
#include "Help.hpp"
#include "SQL.hpp"
#include "Reload.hpp"
#include "Close.hpp"

#include "JSONReader.hpp"

class CommandBuilder : private boost::noncopyable
{
public:
  typedef std::function<std::unique_ptr<ICommand>(void)> Cmds;
public:
  CommandBuilder(void);
  ~CommandBuilder(void);
  std::unique_ptr<ICommand> create(std::string const& name) const;

private:
  std::unique_ptr<ICommand> set(void) const;
  std::unique_ptr<ICommand> dump(void) const;
  std::unique_ptr<ICommand> get(void) const;
  std::unique_ptr<ICommand> help(void) const;
  std::unique_ptr<ICommand> sql(void) const;
  std::unique_ptr<ICommand> reload(void) const;
  std::unique_ptr<ICommand> close(void) const;

  std::unordered_map<std::string, Cmds> _cmds;
};
