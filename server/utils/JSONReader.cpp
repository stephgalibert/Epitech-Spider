//
// JSONReader.cpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 17:15:50 2016 stephane galibert
// Last update Tue Aug 16 11:20:00 2016 stephane galibert
//

#include "JSONReader.hpp"

JSONReader::JSONReader(void)
{
}

JSONReader::~JSONReader(void)
{
}

void JSONReader::readFromString(std::string const& json)
{
  try {
    std::istringstream is(json);
    boost::property_tree::read_json(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}

void JSONReader::readFromFile(std::string const& filename)
{
  try {
    std::ifstream ifs(filename, std::ios::in);
    if (ifs) {
      boost::property_tree::read_json(ifs, _root);
    }
  } catch (std::exception const& e) {
    throw (e);
  }
}

void JSONReader::readFromStream(std::istream &is)
{
  try {
    boost::property_tree::read_json(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}
