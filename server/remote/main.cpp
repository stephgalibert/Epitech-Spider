//
// main.cpp for console in /home/galibe_s/rendu/Spider/server/remote
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  1 19:53:29 2016 stephane galibert
// Last update Mon Nov  7 14:58:01 2016 stephane galibert
//

#include "Console.hpp"

int main(int ac, char **av)
{
  std::string ip = ((ac > 1) ? av[1] : "localhost");
  std::string port = ((ac > 2) ? av[2] : "4242");
  Console console(ip, port);

  try {
    console.init();
    console.start();
    console.close();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
