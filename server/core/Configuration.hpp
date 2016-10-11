//
// Configuration.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 08:23:15 2016 stephane galibert
// Last update Tue Oct  4 21:13:37 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>

#include <boost/noncopyable.hpp>

#include "XMLReader.hpp"

class Configuration : private boost::noncopyable
{
public:
  Configuration(std::string const& rootName);
  ~Configuration(void);

  void read(std::string const& filename);

  template <typename T>
  T getValue(std::string const& nodeName) const
  {
    return (_reader.getValue<T>(_rootName, nodeName));
  }
private:
  std::string _rootName;
  XMLReader _reader;
};
