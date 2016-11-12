//
// FTPConnection.cpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 15:53:03 2016 stephane galibert
// Last update Sat Nov 12 19:57:13 2016 stephane galibert
//

#include "FTPConnection.hpp"
#include "FTPSession.hpp"

FTPConnection::FTPConnection(boost::asio::io_service &io_service,
			     FTPSession &co_manager,
			     PluginManager &pluginManager,
			     std::string const& fname)
  : _co_manager(co_manager),
    _pm(pluginManager),
    _socket(io_service),
    _fname(fname)
{
}

FTPConnection::~FTPConnection(void)
{
}

FTPConnection::Socket& FTPConnection::socket(void)
{
  return (_socket);
}

void FTPConnection::start(void)
{
  boost::filesystem::path path(_fname);

  StaticTools::CreateFolder(path.parent_path().string());
  read();
}

void FTPConnection::write(Packet *packet)
{
  (void)packet;
}

void FTPConnection::write(void)
{
}

void FTPConnection::read(void)
{
  boost::asio::async_read(_socket, _read,
			  boost::asio::transfer_at_least(1),
			  boost::bind(&FTPConnection::do_read,
				      shared_from_this(),
				      boost::asio::placeholders::error,
				      boost::asio::placeholders::bytes_transferred));
}

void FTPConnection::do_write(boost::system::error_code const& ec, size_t)
{
  if (!ec) {
  }
  else {
    _co_manager.leave(shared_from_this());
  }
}

void FTPConnection::do_read(boost::system::error_code const& ec, size_t len)
{
  if (!ec) {
    std::ofstream ofs(_fname, std::ios::app | std::ios::out | std::ios::binary);
    if (ofs) {
      ofs << &_read;
    }
    _read.consume(len);

    read();
  }
  else {
    _co_manager.leave(shared_from_this());
  }
}
