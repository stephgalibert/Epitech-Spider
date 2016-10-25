#pragma once

#include <stdint.h>

#define MAGIC_NUMBER 0x00ABCDEF
#define ERROR_DATA "Error 42: incorrect binary data"
#define ACCESS_DENIED "Error 43: access denied"

enum class PacketType : uint16_t
{
	PT_Error = 0,
	PT_Response = 1,
	PT_NewClient = 2,
	PT_KeyboardEvent = 3,
	PT_MouseEvent = 4,
	PT_Kill = 5,
	PT_Screenshot = 6,
	PT_Command = 7
};

#define PACKED
# pragma pack(push, 1)
# pragma warning(disable : 4200)

struct Packet
{
	unsigned int MAGIC;
	PacketType type;
	int size;
	char data[0];
};

# pragma pack(pop)
#undef PACKED