//
// DeleteFTP.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 18:00:40 2016 stephane galibert
// Last update Sat Nov 12 20:08:39 2016 stephane galibert
//

#include "DeleteFTP.hpp"

DeleteFTP::DeleteFTP(void)
{
}

DeleteFTP::~DeleteFTP(void)
{
}

void DeleteFTP::execute(AConnection::shared own, std::string const& param,
		      Packet **reply)
{
  (void)reply;
  own->deleteFTP(std::atoi(param.c_str()));
}
