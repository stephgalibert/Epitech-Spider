#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "JSONBuilder.h"
#include "JSONReader.h"
#include "RequestBuilder.h"

class TCPClient;

class RequestHandler : private boost::noncopyable
{
public:
  RequestHandler(void);
  ~RequestHandler(void);

  std::string request(TCPClient &client, std::string const& data);

 private:
  std::string cmd(TCPClient &client, JSONReader &reader);
  RequestBuilder _builder;
};
