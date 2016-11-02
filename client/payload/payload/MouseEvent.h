#pragma once

#include <stdint.h>

enum class MouseEvent : uint16_t
{
	ME_None = 0,
	ME_Left = 1,
	ME_Right = 2
};