#include "Kill.h"
#include "TCPClient.h"

Kill::Kill(void)
{
}

Kill::~Kill(void)
{
}

std::string Kill::execute(TCPClient &client, JSONReader &reader)
{
	(void)reader;
	(void)client;
	exit(1);
	return ("");
}