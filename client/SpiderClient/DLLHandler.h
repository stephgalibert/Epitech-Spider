#pragma once

#include <string>

#include <Windows.h>

class DLLHandler
{
public:
	DLLHandler(void);
	~DLLHandler(void);

	void loadLibrary(std::string const& lib);
	FARPROC getSymbolAddr(std::string const& symName);
private:
	HMODULE _dll;
	std::string _name;
};