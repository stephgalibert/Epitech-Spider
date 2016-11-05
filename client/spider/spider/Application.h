#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>

#include "Distributor.h"
#include "StaticTools.h"
#include "IPayload.h"

#include <Windows.h>
#include <ShlObj.h>
#include <TlHelp32.h>

#include "WinDlLoader.h"

# define APP_NAME "spider.exe"

class Application
{
public:
	Application(std::string const& appliPath);
	~Application(void);

	void init(void);
	void loop(void);
	void close(void);

	static bool Existing(void);

private:
	std::string _appliPath;
	WinDlLoader<IPayload> _dllLoader;

	IPayload *_payload;
	std::shared_ptr<IDistributor> _distributor;
};
