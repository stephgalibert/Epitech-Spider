#pragma once

#include "IRequest.h"

class Kill : public IRequest
{
public:
	Kill(void);
	virtual ~Kill(void);

	virtual void execute(IClient &client, std::string const& param, Packet **toSend);
};

