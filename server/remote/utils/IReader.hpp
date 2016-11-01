//
// IReader.hpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 07:31:56 2016 stephane galibert
// Last update Tue Oct  4 21:13:54 2016 stephane galibert
//

#pragma once

#include <istream>
#include <string>

#include <boost/noncopyable.hpp>

struct IReader : private boost::noncopyable
{
  virtual ~IReader(void) {}
  virtual void readFromString(std::string const& data) = 0;
  virtual void readFromFile(std::string const& filename) = 0;
  virtual void readFromStream(std::istream &is) = 0;
};
