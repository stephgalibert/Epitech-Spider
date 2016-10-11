#pragma once

#include "JSONReader.h"

class TCPClient;

struct IRequest
{
	virtual ~IRequest(void) {}
	virtual std::string execute(TCPClient &client, JSONReader &reader) = 0;
};