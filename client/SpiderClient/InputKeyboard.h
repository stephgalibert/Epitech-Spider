#pragma once

#include <boost/chrono.hpp>

#include "AInputType.h"
#include "StaticTools.h"

class InputKeyboard : public AInputType
{
public:
	InputKeyboard(void);
	virtual ~InputKeyboard(void);

	virtual void format(std::streamoff logSize);
	virtual AInputType &operator>>(LogFile &logger);
	virtual AInputType &operator>>(TCPClient &client);
private:
	std::string _format;
	static boost::chrono::system_clock::time_point LastKeyboardActivity;
	static std::string PreviousWindow;
};
