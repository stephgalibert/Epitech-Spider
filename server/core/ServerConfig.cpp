//
// ServerConfig.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 04:02:38 2016 stephane galibert
// Last update Wed Aug 17 04:04:57 2016 stephane galibert
//

#include "ServerConfig.hpp"

ServerConfig::ServerConfig(void)
  : Configuration("server")
{
}

ServerConfig::~ServerConfig(void)
{
}

std::string ServerConfig::getPassword(void) const
{
  return (getValue<std::string>("pwd"));
}

size_t ServerConfig::getVersion(void) const
{
  return (getValue<size_t>("version"));
}
