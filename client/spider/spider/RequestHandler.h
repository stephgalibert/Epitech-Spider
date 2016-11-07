#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "IClient.h"
#include "RequestBuilder.h"
#include "Protocol.h"
#include "StaticTools.h"

class TCPClient;

class RequestHandler : private boost::noncopyable
{
public:
  RequestHandler(void);
  ~RequestHandler(void);

  void request(IClient &client, Packet const *received, Packet **toSend);

 private:
  RequestBuilder _builder;
};
