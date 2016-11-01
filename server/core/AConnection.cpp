//
// AConnection.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug 12 03:22:40 2016 stephane galibert
// Last update Tue Nov  1 20:17:31 2016 stephane galibert
//

#include "AConnection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

AConnection::AConnection(boost::asio::io_service &io_service,
			 ConnectionManager &co_manager,
			 RequestHandler &reqHandler,
			 PluginManager &pluginManager,
			 ServerConfig &config)
  : _io_service(io_service),
    _co_manager(co_manager),
    _reqHandler(reqHandler),
    _pluginManager(pluginManager),
    _config(config)
{
  _privilege = Privilege::PL_USER;
  _running = false;
}

AConnection::~AConnection(void)
{
}

void AConnection::setMacAddress(std::string const& mac)
{
  _mac = mac;
}

std::string const& AConnection::getMacAddress(void) const
{
  return (_mac);
}

void AConnection::setPrivilege(Privilege value)
{
  _privilege = value;
}

Privilege AConnection::getPrivilege(void) const
{
  return (_privilege);
}

void AConnection::close(void)
{
  _running = false;
  _io_service.stop();
}

void AConnection::reloadPlugin(void)
{
  _pluginManager.closeAll();
  StaticTools::LoadPlugin(_pluginManager);
}

bool AConnection::closePlugin(std::string const& name)
{
  return (_pluginManager.close(name));
}

void AConnection::connectToDB(void)
{
  if (isRegistered()) {
    _pluginManager.newConnectionDatabase(_mac);
  }
}

void AConnection::disconnectToDB(void)
{
  if (isRegistered()) {
    _pluginManager.lostConnectionDatabase(_mac);
  }
}

bool AConnection::isRegistered(void) const
{
  return (_mac.size() == 12);
}

void AConnection::addLog(std::string const& toadd)
{
  if (isRegistered()) {
    _pluginManager.newKeyDatabase(_mac, toadd);
  }
}

std::string AConnection::executeSQL(std::string const& stmt)
{
  return (_pluginManager.executeSQLDatabase(stmt));
}

std::vector<PluginInfo> const AConnection::getPluginsInfo(void) const
{
  return (_pluginManager.getPluginsInfo());
}

ServerConfig const& AConnection::getServerConfig(void) const
{
  return (_config);
}
