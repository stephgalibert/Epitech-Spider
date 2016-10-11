#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <list>

#include <boost/core/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class JSONBuilder : private boost::noncopyable
{
public:
  JSONBuilder(void);
  ~JSONBuilder(void);

  void read(std::string const& json);

  template <typename T>
  void addValue(std::string const& nodeName, T value)
  {
    _root.put(nodeName, value);
  }

  template <typename T>
  void addListValues(std::string const& nodeName, std::vector<T> const& list)
  {
    boost::property_tree::ptree nodes;
    for (auto &it : list) {
      boost::property_tree::ptree node;
      node.put("", it);
      nodes.push_back(std::make_pair("", node));
    }
    _root.add_child(nodeName, nodes);
  }

  template <typename T>
  void addArrayValues(std::string const& nodeName, std::vector<T> const& list)
  {
    boost::property_tree::ptree nodeObject;

    for (auto &it : list) {
      boost::property_tree::ptree nodeData;

      nodeData.put(it.first, it.second);
      nodeObject.push_back(std::make_pair("", nodeData));
    }
    _root.add_child(nodeName, nodeObject);
  }

  std::string get(void);
private:
  boost::property_tree::ptree _root;
};

template<>
inline void JSONBuilder::addListValues(std::string const& nodeName, std::vector<std::pair<std::string, std::string> > const& list)
{
  boost::property_tree::ptree nodes;
  for (auto &it : list) {
    nodes.put(it.first, it.second);
  }
  _root.add_child(nodeName, nodes);
}
