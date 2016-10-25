//
// StaticTools.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:29 2016 stephane galibert
// Last update Mon Oct 24 18:05:47 2016 stephane galibert
//

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Protocol.hpp"

class StaticTools
{
public:
  static std::string GetDate(void);
  static std::string GetHour(void);
  static Packet *CreatePacket(PacketType type, std::string const& data);
};
