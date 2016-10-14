#pragma once

#include "JSONReader.h"
#include "IClient.h"

struct IRequest
{
	virtual ~IRequest(void) {}
	virtual std::string execute(IClient &client, JSONReader &reader) = 0;
};