//
// FTPConnection.cpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Nov  8 15:53:03 2016 stephane galibert
// Last update Tue Nov  8 21:40:16 2016 stephane galibert
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
  //handshake();
  //std::string id = _fname.substr(_fname.find_first_of("/"),  _fname.find_last_of("/"));
  boost::filesystem::path path(_fname);
  //path.parent_path()

  std::clog << "id: " << "-" << " parent: " << path.parent_path().string() << std::endl;
  StaticTools::CreateFolder(path.parent_path().string());
  read();
}

void FTPConnection::write(Packet *packet)
{
  (void)packet;
  /*bool write_in_progress = !_toWrites.empty();

  _toWrites.push(packet);
  if (!write_in_progress) {
    write();
    }/*/
}

void FTPConnection::write(void)
{
  /*Packet *packet = _toWrites.front();

  boost::asio::async_write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size),
			   boost::bind(&FTPConnection::do_write,
				       shared_from_this(),
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred));*/
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

/*void FTPConnection::handshake(void)
{
  _socket.async_handshake(boost::asio::ssl::stream_base::server,
			  boost::bind(&AConnection::do_handshake, shared_from_this(),
				      boost::asio::placeholders::error));
				      }*/

void FTPConnection::do_write(boost::system::error_code const& ec, size_t)
{
  if (!ec) {
    /*Packet *packet = _toWrites.front();
    free(packet);

    _toWrites.pop();

    if (!_toWrites.empty()) {
      write();
      }*/
  }
  else {
    _co_manager.leave(shared_from_this());
  }
}

void FTPConnection::do_read(boost::system::error_code const& ec, size_t len)
{
  if (!ec) {
    /*std::string s((std::istreambuf_iterator<char>(&_read)),
      std::istreambuf_iterator<char>());*/
    // std::cout << "ftp read: size: " << _read.size() << " data: '" << s << "'" << std::endl;
    std::ofstream ofs(_fname, std::ios::app | std::ios::out | std::ios::binary);
    if (ofs) {
      ofs << &_read;
    }
    _read.consume(len);
    /*Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
    _read.consume(len);

    Packet *reply = NULL;
    _reqHandler.request(shared_from_this(), packet, &reply);

    if (reply) {
      write(reply);
      }*/

    //if (_running) {
    read();
    //}
  }
  else {
    _co_manager.leave(shared_from_this());
  }
}
