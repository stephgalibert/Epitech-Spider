#pragma once

#include "IClient.h"
#include "Protocol.h"

struct IRequest
{
	virtual ~IRequest(void) {}
	virtual void execute(IClient &client, std::string const& param, Packet **toSend) = 0;
};