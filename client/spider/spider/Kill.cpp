#include "Kill.h"
Kill::Kill(void)
{
}

Kill::~Kill(void)
{
}

std::string Kill::execute(IClient &client, JSONReader &reader)
{
	(void)reader;
	(void)client;
	exit(1);
	return ("");
}