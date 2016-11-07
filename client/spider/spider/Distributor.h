#pragma once

#include <iostream>
#include <string>
#include <cstdio>

#include "UDPClient.h"
#include "TCPClient.h"
#include "LogFile.h"
#include "IDistributor.h"
#include "XMLReader.h"

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

	IClient *_client;
	LogFile _log;
	LogFile _tosend;
};

