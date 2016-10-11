//
// StaticTools.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:29 2016 stephane galibert
// Last update Mon Aug 22 19:25:45 2016 stephane galibert
//

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include <boost/date_time/posix_time/posix_time.hpp>

class StaticTools
{
public:
  static std::string GetDate(void);
  static std::string GetHour(void);
};
