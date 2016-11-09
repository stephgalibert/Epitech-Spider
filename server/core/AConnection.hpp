//
// AConnection.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug 12 03:01:15 2016 stephane galibert
// Last update Wed Nov  9 03:59:55 2016 stephane galibert
//

#pragma once

#include <string>
#include <vector>
#include <list>

#include <boost/asio.hpp>

#include "StaticTools.hpp"
#include "PluginManager.hpp"
#include "ServerConfig.hpp"
#include "Privilege.hpp"
#include "Protocol.hpp"
#include "FTPServer.hpp"

class RequestHandler;
class ConnectionManager;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
  typedef std::shared_ptr<AConnection> shared;
public:
  AConnection(boost::asio::io_service &io_service,
	      RequestHandler &reqHandler,
	      PluginManager &pluginManager,
	      ConnectionManager &cm,
	      ServerConfig &config);
  virtual ~AConnection(void);

  virtual void start(void) = 0;
  virtual void write(Packet *packet) = 0;

  virtual void do_write(boost::system::error_code const& ec, size_t len) = 0;
  virtual void do_read(boost::system::error_code const& ec, size_t len) = 0;
  virtual void do_handshake(boost::system::error_code const& ec) = 0;

  virtual void addLog(std::string const& toadd) = 0;
  virtual void connectDB(void) = 0;
  virtual void disconnectDB(void) = 0;

  void setMacAddress(std::string const& mac);
  std::string const& getMacAddress(void) const;

  void setPrivilege(Privilege value);
  Privilege getPrivilege(void) const;

  void close(void);
  bool closePlugin(std::string const& name);
  void reloadPlugin(void);
  bool isRegistered(void) const;
  std::string executeSQL(std::string const& stmt);
  std::vector<PluginInfo> const getPluginsInfo(void) const;
  ServerConfig const& getServerConfig(void) const;

  unsigned short createFTP(std::string const& filename);
  void deleteFTP(unsigned short port);

  void enableRedirection(bool value);
  bool redirectionActive(void) const;
  void broadcast(std::string const& msg);

  void listen(std::string const& mac, bool enable);
  bool isListened(std::string const& mac) const;

protected:
  std::list<std::string> _listened;
  std::list<FTPServer *> _ftps;
  boost::asio::io_service &_io_service;
  RequestHandler &_reqHandler;
  PluginManager &_pluginManager;
  ConnectionManager &_co_manager;
  ServerConfig &_config;
  Privilege _privilege;
  std::string _mac;
  bool _running;
  bool _redirection;
};
