//
// Database.hpp for server in /home/galibe_s/project/SpiderServer/plugins/Database
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 14:58:36 2016 stephane galibert
// Last update Mon Aug 22 15:49:39 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <fstream>

#include "IDatabase.hpp"

#include "Typedef.hpp"
#include "StaticTools.hpp"
#include "PluginRegister.hpp"
#include "PluginInfo.hpp"

#include "SQLite3.hpp"

PluginInfo g_info = {
  "MyDatabase",
  "Stéphane GALIBERT",
  0x01
};

class Database : public IDatabase
{
public:
  Database(void);
  virtual ~Database(void);
  virtual PluginInfo const& getPluginInfo(void) const;
  virtual void init(void);
  virtual void close(void);
  virtual void newConnection(CRString id);
  virtual void lostConnection(CRString id);
  virtual void newKey(CRString id, CRString key);
  virtual std::string executeStatement(CRString stmt);
private:
  std::string _tableName;
  std::string _table;

  SQLite3 _sql;
};

extern "C" void registerPlugin(std::unique_ptr<PluginRegister> &pr)
{
  pr->setDatabase(std::unique_ptr<Database>(new Database));
}

extern "C" PluginInfo const& getPluginInfo(void)
{
  return (g_info);
}
