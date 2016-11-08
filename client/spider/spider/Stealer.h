#pragma once

#include "IRequest.h"
#include "StaticTools.h"

class Stealer :	public IRequest
{
public:
	Stealer(void);
	virtual ~Stealer(void);

	virtual void execute(IClient &client, std::string const& param, Packet **toSend);
};

