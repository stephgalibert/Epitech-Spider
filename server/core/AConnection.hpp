//
// AConnection.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug 12 03:01:15 2016 stephane galibert
// Last update Wed Oct 19 14:44:33 2016 stephane galibert
//

#pragma once

#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "StaticTools.hpp"
#include "PluginManager.hpp"
#include "ServerConfig.hpp"
#include "Privilege.hpp"
#include "Protocol.hpp"

class ConnectionManager;
class RequestHandler;

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
  typedef std::shared_ptr<AConnection> shared;
public:
  AConnection(boost::asio::io_service &io_service,
	      ConnectionManager &co_manager,
	      RequestHandler &reqHandler,
	      PluginManager &pluginManager,
	      ServerConfig &config);
  virtual ~AConnection(void);

  virtual void start(void) = 0;
  virtual void write(Packet *packet) = 0;

  virtual void do_write(boost::system::error_code const& ec, size_t len) = 0;
  virtual void do_read(boost::system::error_code const& ec, size_t len) = 0;
  virtual void do_handshake(boost::system::error_code const& ec) = 0;

  void setMacAddress(std::string const& mac);
  std::string const& getMacAddress(void) const;

  void setPrivilege(Privilege value);
  Privilege getPrivilege(void) const;

  void close(void);
  void reloadPlugin(void);
  void connectToDB(void);
  void disconnectToDB(void);
  bool isRegistered(void) const;
  void addLog(std::string const& toadd);
  std::string executeSQL(std::string const& stmt);
  std::vector<PluginInfo> const& getPluginsInfo(void) const;
  ServerConfig const& getServerConfig(void) const;

protected:
  boost::asio::io_service &_io_service;
  ConnectionManager &_co_manager;
  RequestHandler &_reqHandler;
  PluginManager &_pluginManager;
  ServerConfig &_config;
  Privilege _privilege;
  std::string _mac;
  bool _running;
};
