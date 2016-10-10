#include "AInputType.h"

AInputType::AInputType(void)
{
}

AInputType::~AInputType(void)
{
}

AInputType &AInputType::operator<<(std::string const& data)
{
	_data = data;
	return (*this);
}