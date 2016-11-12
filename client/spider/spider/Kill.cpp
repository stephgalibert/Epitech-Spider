#include "Kill.h"

Kill::Kill(void)
{
}

Kill::~Kill(void)
{
}

void Kill::execute(IClient &client, std::string const& param, Packet **toSend)
{
	(void)param;
	(void)toSend;
	(void)client;
	exit(1);
}