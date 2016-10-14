#pragma once

#include <string>

class IClient
{
public:
	virtual ~IClient(void) {}

	virtual void connect(std::string const& remote, std::string const& port) = 0;
	virtual void write(std::string const& data) = 0;
	virtual void disconnect(void) = 0;

	virtual void run(void) = 0;

	virtual bool isConnected(void) const = 0;

	virtual IClient &operator<<(std::string const& data) = 0;
};