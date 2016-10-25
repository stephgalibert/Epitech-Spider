//
// RequestHandler.hpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:12 2016 stephane galibert
// Last update Tue Oct 25 16:36:42 2016 stephane galibert
//

#pragma once

#include <string>

#include <boost/noncopyable.hpp>

#include "Protocol.hpp"
#include "StaticTools.hpp"
#include "Privilege.hpp"
#include "AConnection.hpp"

#include "JSONReader.hpp"

#include "RequestBuilder.hpp"
#include "CommandBuilder.hpp"

class RequestHandler : private boost::noncopyable
{
public:
  RequestHandler(void);
  ~RequestHandler(void);

  void request(AConnection::shared own, Packet const *received, Packet **reply);

 private:
  void createReq(AConnection::shared own, Packet const *received, Packet **reply);
  void createCmd(AConnection::shared own, Packet const *received, Packet **reply);

  RequestBuilder _reqBuilder;
  CommandBuilder _cmdBuilder;
};
