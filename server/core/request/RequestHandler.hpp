//
// RequestHandler.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:12 2016 stephane galibert
// Last update Wed Oct 19 15:15:21 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "StaticTools.hpp"
#include "Privilege.hpp"
#include "JSONBuilder.hpp"
#include "JSONReader.hpp"
#include "AConnection.hpp"
#include "RequestBuilder.hpp"

class RequestHandler : private boost::noncopyable
{
public:
  RequestHandler(void);
  ~RequestHandler(void);

  void request(AConnection::shared own, Packet const* received, Packet **reply);

 private:
  //std::string cmd(AConnection::shared own, JSONReader &reader);
  RequestBuilder _builder;
};
