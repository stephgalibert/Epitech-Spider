#include "DLLHandler.h"

DLLHandler::DLLHandler(void)
{
	_dll = NULL;
}

DLLHandler::~DLLHandler(void)
{
	if (_dll) {
		FreeLibrary(_dll);
	}
}

void DLLHandler::loadLibrary(std::string const& lib)
{
	_name = lib;
	if (_dll) {
		FreeLibrary(_dll);
	}
	_dll = LoadLibrary(lib.c_str());
	if (!_dll) {
		throw std::runtime_error(lib + ": not found");
	}
}

FARPROC DLLHandler::getSymbolAddr(std::string const& symName)
{
	FARPROC sym = GetProcAddress(_dll, symName.c_str());
	if (!sym) {
		throw std::runtime_error(_name + ": " + symName + " not found");
	}
	return (sym);
}

