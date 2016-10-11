//
// ServerConfig.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 17 04:00:48 2016 stephane galibert
// Last update Wed Aug 17 04:04:09 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>

#include "Configuration.hpp"

class ServerConfig : public Configuration
{
public:
  ServerConfig(void);
  ~ServerConfig(void);

  std::string getPassword(void) const;
  size_t getVersion(void) const;
};
