//
// StaticTools.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:34 2016 stephane galibert
// Last update Mon Oct 24 18:06:06 2016 stephane galibert
//

#include "StaticTools.hpp"

std::string StaticTools::GetDate(void)
{
  std::stringstream ss;
  boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
  ss << std::right << now.date().day() << "/"
     << now.date().month() << "/"
		<< now.date().year() << " - "
     << std::setw(2) << std::setfill('0') << now.time_of_day().hours() << "h"
     << std::setw(2) << std::setfill('0') << now.time_of_day().minutes() << "m"
     << std::setw(2) << std::setfill('0') << now.time_of_day().seconds() << "s"
     << std::flush;
  return (ss.str());
}

std::string StaticTools::GetHour(void)
{
  std::stringstream ss;

  boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
  ss << std::setw(2) << std::setfill('0') << now.time_of_day().hours() << "h"
     << std::setw(2) << std::setfill('0') << now.time_of_day().minutes() << "m"
     << std::setw(2) << std::setfill('0') << now.time_of_day().seconds() << "s"
     << std::flush;
  return (ss.str());
}

void StaticTools::CreateFolder(std::string const& path)
{
  boost::filesystem::create_directory(path);
}

bool StaticTools::CheckMacValidity(std::string const& mac)
{
  return (mac.size() == 12);
}

void StaticTools::LoadPlugin(PluginManager &pm)
{
  PluginLoader pluginLoader;

  pluginLoader.parseDirectory("./plugins/");
  std::vector<std::string> const& plugins = pluginLoader.getPlugins();

  for (auto it : plugins) {
    pm.load(it);
  }
}

Packet *StaticTools::CreatePacket(PacketType type, std::string const& data)
{
  size_t i = 0;
  Packet *packet;

  packet = (Packet *)malloc(sizeof(Packet) + (data.size() * sizeof(char) + 1));
  packet->MAGIC = MAGIC_NUMBER;
  packet->type = type;
  packet->size = data.size();
  while (i < data.size()) {
    packet->data[i] = data[i];
    ++i;
  }
  packet->data[i] = 0;
  return (packet);
}
