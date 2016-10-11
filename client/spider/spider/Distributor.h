#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <cstdio>

#include "JSONBuilder.h"
#include "AInputType.h"
#include "LogFile.h"
#include "TCPClient.h"

#include <Windows.h>

class Distributor : private std::enable_shared_from_this<Distributor>
{
public:
	Distributor();
	~Distributor();

	void init(void);
	void destroy(void);

	Distributor &operator<<(AInputType &entry);

private:
	void sendToSend(void);

	TCPClient _client;
	LogFile _log;
	LogFile _tosend;
};

