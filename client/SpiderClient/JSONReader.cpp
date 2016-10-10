#include "JSONReader.h"

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
