//
// DeleteFTP.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 18:00:12 2016 stephane galibert
// Last update Tue Nov  8 18:01:07 2016 stephane galibert
//

#pragma once

#include "IRequest.hpp"

class DeleteFTP : public IRequest
{
public:
  DeleteFTP(void);
  virtual ~DeleteFTP(void);

  virtual void execute(AConnection::shared own, std::string const& param,
		       Packet **reply);
};
