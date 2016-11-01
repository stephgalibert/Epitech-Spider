//
// SQLite3.hpp for server in /home/galibe_s/project/SpiderServer/plugins/Database
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Aug 20 10:36:41 2016 stephane galibert
// Last update Wed Oct 26 11:52:40 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include <sqlite3.h>

#include "Typedef.hpp"
#include "JSONBuilder.hpp"

int callback(void *data, int ac, char **av, char **azColName);

class SQLite3
{
public:
  SQLite3(CRString path);
  ~SQLite3(void);

  void createTable(CRString table);
  void close(void);

  void insert(CRString table, CRString colName, CRString value);
  void select(CRString table, CRString id, CRString idValue);
  void update(CRString table, CRString colName, CRString nValue, CRString id,
	      CRString idValue);
  void erase(CRString table, CRString id, CRString idValue);
  bool exist(CRString table, CRString colName, CRString value);
  std::string execute(CRString q);
  void open(void);
private:
  void exec(CRString query, int (*callback)(void *, int, char **, char **));

  std::string _path;
  sqlite3 *_db;
};
