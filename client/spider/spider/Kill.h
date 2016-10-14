#pragma once

#include "IRequest.h"

class Kill : public IRequest
{
public:
	Kill(void);
	virtual ~Kill(void);
	virtual std::string execute(IClient &client, JSONReader &reader);
};

