//
// JSONReader.hpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 17:14:53 2016 stephane galibert
// Last update Wed Aug 17 04:39:55 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include <vector>
#include <list>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "IReader.hpp"

class JSONReader : public IReader
{
public:
  JSONReader(void);
  virtual ~JSONReader(void);

  virtual void readFromString(std::string const& json);
  virtual void readFromFile(std::string const& filename);
  virtual void readFromStream(std::istream &is);

  template <typename T>
  T getValue(std::string const& nodeName) const
  {
    return (_root.get<T>(nodeName));
  }

  template <typename T>
  void getListValues(std::string const& nodeName, std::vector<T> &list) const
  {
    for (boost::property_tree::ptree::value_type const& node
	   : _root.get_child(nodeName)) {
      list.push_back(std::make_pair(node.first.data(), node.second.data()));
    }
  }

  template <typename T>
  void getArrayValues(std::string const& arrayName,
		      std::vector<std::vector<T> > &list) const
  {
    for (boost::property_tree::ptree::value_type const& row : _root.get_child(arrayName)) {
      std::vector<T> tmp;
      for (boost::property_tree::ptree::value_type const& subrow : row.second) {
	tmp.push_back(std::make_pair(subrow.first,
				     subrow.second.get_value<std::string>()));
      }
      list.push_back(tmp);
    }
  }

private:
  boost::property_tree::ptree _root;
};
