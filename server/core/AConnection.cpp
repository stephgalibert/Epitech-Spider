//
// AConnection.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 15:46:09 2016 stephane galibert
// Last update Wed Nov  9 14:11:49 2016 stephane galibert
//

#include "AConnection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"

AConnection::AConnection(boost::asio::io_service &io_service,
			 RequestHandler &reqHandler,
			 PluginManager &pluginManager,
			 ConnectionManager &cm,
			 ServerConfig &config)
  : _io_service(io_service),
    _reqHandler(reqHandler),
    _pluginManager(pluginManager),
    _co_manager(cm),
    _config(config),
    _privilege(Privilege::PL_USER),
    _running(false)
{
}

AConnection::~AConnection(void)
{
  for (auto it : _ftps) {
    it->close();
    delete (it);
  }
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

bool AConnection::isRegistered(void) const
{
  return (_mac.size() > 0);
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

unsigned short AConnection::createFTP(std::string const& filename)
{
  if (!isRegistered())
    return (0);
  std::string file = "./clients/" + _mac + "/" + filename;

  //std::clog << "ftp filename: " << file << std::endl;

  std::list<FTPServer *>::iterator it = _ftps.begin();
  while (it != _ftps.end()) {
    if (!(*it)->inUse()) {
      //std::clog << "reusing " << (*it)->getPort() << std::endl;
      (*it)->setInUse(true);
      (*it)->setFilename(file);
      return ((*it)->getPort());
    }
    ++it;
  }

  FTPServer *ftp = new FTPServer(_io_service, _pluginManager, file);

  ftp->open();
  _ftps.push_front(ftp);

  //std::clog << "create new ftp server :" << ftp->getPort() << std::endl;
  return (ftp->getPort());
}

void AConnection::deleteFTP(unsigned short port)
{
  std::list<FTPServer *>::iterator it = _ftps.begin();
  while (it != _ftps.end()) {
    if ((*it)->getPort() == port) {
      (*it)->setInUse(false);
      break;
    }
    ++it;
  }
}

void AConnection::listen(std::string const& mac, bool enable)
{
  if (enable) {
    _listened.push_front(mac);
  } else {
    std::list<std::string>::iterator it = _listened.begin();
    while (it != _listened.end()) {
      if ((*it) == mac) {
	it = _listened.erase(it);
      } else {
	++it;
      }
    }
  }
}

bool AConnection::isListened(std::string const& mac) const
{
  for (auto &it : _listened) {
    if (it == mac) {
      return (true);
    }
  }
  return (false);
}
