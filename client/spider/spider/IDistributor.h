#pragma once

#include <memory>

#include "AInputType.h"

struct IDistributor : private std::enable_shared_from_this<IDistributor>
{
	virtual ~IDistributor(void) {}
	virtual void init(void) = 0;
	virtual void destroy(void) = 0;
	virtual IDistributor &operator<<(AInputType &entry) = 0;
};