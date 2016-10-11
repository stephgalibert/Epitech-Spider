#pragma once

#include <string>

#include "TCPClient.h"
#include "LogFile.h"
#include "JSONBuilder.h"

class AInputType
{
public:
	AInputType(void);
	virtual ~AInputType(void);

	AInputType &operator<<(std::string const& data);
	virtual void format(std::streamoff logSize) = 0;
	virtual AInputType &operator>>(LogFile &logger) = 0;
	virtual AInputType &operator>>(TCPClient &client) = 0;

protected:
	std::string _data;
};
