#pragma once

#include <iostream>
#include <string>
#include <cstdio>

#include "TCPClient.h"
#include "JSONBuilder.h"
#include "LogFile.h"
#include "IDistributor.h"

class Distributor : public IDistributor
{
public:
	Distributor(void);
	virtual ~Distributor(void);

	virtual void init(void);
	virtual void destroy(void);

	virtual IDistributor &operator<<(AInputType &entry);

private:
	void sendToSend(void);

	TCPClient _client;
	LogFile _log;
	LogFile _tosend;
};

