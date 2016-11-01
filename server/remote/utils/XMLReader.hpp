//
// XMLReader.hpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 07:34:10 2016 stephane galibert
// Last update Tue Aug 16 08:43:30 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "IReader.hpp"

class XMLReader :  public IReader
{
public:
  XMLReader(void);
  virtual ~XMLReader(void);

  virtual void readFromString(std::string const& json);
  virtual void readFromFile(std::string const& filename);
  virtual void readFromStream(std::istream &is);

  template <typename T>
  T getValue(std::string const& rootName, std::string const& nodeName) const
  {
    return (_root.get<T>(rootName + "." + nodeName));
  }
private:
  boost::property_tree::ptree _root;
};
