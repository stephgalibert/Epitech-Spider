#include "StaticTools.h"

std::string StaticTools::GetMacAddress(void)
{
	ULONG size = sizeof(IP_ADAPTER_INFO);
	std::stringstream ss;
	PIP_ADAPTER_INFO adapter = new IP_ADAPTER_INFO;

	if (GetAdaptersInfo(adapter, &size) == ERROR_SUCCESS) {
		ss << std::hex << (int)adapter->Address[0] << std::hex << (int)adapter->Address[1]
			<< std::hex << (int)adapter->Address[2] << std::hex << (int)adapter->Address[3]
			<< std::hex << (int)adapter->Address[4] << std::hex << (int)adapter->Address[5]
			<< std::flush;
		delete (adapter);
		return (ss.str());
	}
	delete (adapter);
	return ("");
}

std::streamoff StaticTools::GetFileSize(std::string const& filename)
{
	std::ifstream in(filename.c_str(), std::ifstream::ate | std::ifstream::binary);
	return (in.tellg());
}

std::string StaticTools::GetActiveWindowTitle()
{
	char title[256];
	HWND hwnd = GetForegroundWindow();

	GetWindowText(hwnd, title, sizeof(title));

	return (title);
}

std::string StaticTools::GetDate(void)
{
	std::stringstream ss;
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	ss << std::right << now.date().day() << "/"
		<< now.date().month() << "/"
		<< now.date().year() << " - "
		<< std::setw(2) << std::setfill('0') << now.time_of_day().hours() << "h"
		<< std::setw(2) << std::setfill('0') << now.time_of_day().minutes() << "m"
		<< std::setw(2) << std::setfill('0') << now.time_of_day().seconds() << "s" << std::flush;
	return (ss.str());
}

std::string StaticTools::GetFolderPath(WORD id)
{
	CHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, id, NULL, 0, szPath))) {
		return (szPath);
	}
	throw (std::runtime_error(std::string("Folder " + std::to_string(id) + " not found")));
}

std::string StaticTools::GetProjectResourceDirectory(void)
{
	return (StaticTools::GetFolderPath(CSIDL_APPDATA) + "\\spider");
}

void StaticTools::CreateFolder(std::string const& path)
{
	if (!boost::filesystem::exists(path)) {
		if (!boost::filesystem::create_directory(path))
			throw (std::runtime_error("can not create spider folder '" + path + "'"));
	}
}

std::string StaticTools::GetDLLPath(std::string const& appPath)
{
	std::string dllName(DLL_NAME);
	std::string ret;

	ret = appPath.substr(0, appPath.find_last_of('\\'));
	ret += "\\" + dllName;
	return (ret);
}