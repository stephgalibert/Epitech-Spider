#pragma once

#include "AInputType.h"

class InputMouse : public AInputType
{
public:
	InputMouse(void);
	virtual ~InputMouse();

	virtual void format(std::streamoff logSize);
	virtual AInputType &operator>>(LogFile &logger);
	virtual AInputType &operator>>(TCPClient &client);
private:
	std::string _format;
};