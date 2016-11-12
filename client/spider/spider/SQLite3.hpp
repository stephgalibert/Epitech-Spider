#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "sqlite3.h"

#include "Typedef.hpp"
#include "JSONBuilder.hpp"

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
  std::string execute(CRString q, std::string name);
private:
  void open(CRString path);
  void exec(CRString query, int (*callback)(void *, int, char **, char **));

  std::string _path;
  sqlite3 *_db;
};
