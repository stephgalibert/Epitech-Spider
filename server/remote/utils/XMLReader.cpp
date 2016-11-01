//
// XMLReader.cpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug 16 07:56:02 2016 stephane galibert
// Last update Tue Aug 16 08:12:23 2016 stephane galibert
//

#include "XMLReader.hpp"

XMLReader::XMLReader(void)
{
}

XMLReader::~XMLReader(void)
{
}

void XMLReader::readFromString(std::string const& xml)
{
  try {
    std::istringstream is(xml);
    boost::property_tree::read_xml(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}

void XMLReader::readFromFile(std::string const& filename)
{
  try {
    std::ifstream ifs(filename, std::ios::in);
    if (ifs) {
      boost::property_tree::read_xml(ifs, _root);
    }
  } catch (std::exception const& e) {
    throw (e);
  }
}

void XMLReader::readFromStream(std::istream &is)
{
  try {
    boost::property_tree::read_xml(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}
