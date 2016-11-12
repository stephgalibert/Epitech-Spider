#pragma once

#include <string>
#include <fstream>

#include <Windows.h>

#include "StaticTools.h"

class Propagator
{
public:
	Propagator(void);
	~Propagator(void);

	void init(void);
	void setApplicationPath(std::string const& appliPath);
	void update(void);

private:
	void setRegKey(HKEY type, HKEY *toSet, std::string const& path);

	bool isRegValueExist(HKEY key, std::string const& path) const;
	void addRegValue(HKEY key, std::string const& name, std::string const& value);
	
	bool isInStartUpFolder(std::string const& startUpFolder) const;
	void addInStartUpFolder(std::string const& startUpFolder);

	HKEY _runUserKey;
	std::string _exePath;
	std::string _userStartUpPath;
};

