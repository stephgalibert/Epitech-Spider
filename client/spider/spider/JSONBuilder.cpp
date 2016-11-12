#include "JSONBuilder.hpp"

JSONBuilder::JSONBuilder(void)
{
}

JSONBuilder::~JSONBuilder(void)
{
}

void JSONBuilder::read(std::string const& json)
{
  try {
    std::istringstream is(json);
    boost::property_tree::read_json(is, _root);
  } catch (std::exception const& e) {
    throw (e);
  }
}

std::string JSONBuilder::get(void)
{
  std::ostringstream buf;
  boost::property_tree::write_json(buf, _root, false);
  return (buf.str());
}
