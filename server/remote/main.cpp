//
// main.cpp for console in /home/galibe_s/rendu/Spider/server/remote
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  1 19:53:29 2016 stephane galibert
// Last update Tue Nov  1 20:04:13 2016 stephane galibert
//

#include "Console.hpp"

int	main(void)
{
  Console console;

  console.init();
  console.start();
  console.close();
  return (0);
}
