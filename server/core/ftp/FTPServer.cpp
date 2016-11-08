//
// FTPServer.cpp for server in /home/galibe_s/rendu/Spider/server/core/ftp
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Nov  7 17:21:45 2016 stephane galibert
// Last update Tue Nov  8 21:26:44 2016 stephane galibert
//

#include "FTPServer.hpp"

FTPServer::FTPServer(boost::asio::io_service &ios, PluginManager &pm,
		     std::string const& f)
  : _io_service(ios),
    _pm(pm),
    _filename(f),
    _acceptor(_io_service),
    _inUse(true)
{
  boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
  _acceptor.open(endPoint.protocol());
  _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  _acceptor.bind(endPoint);

  _acceptor.listen();

  boost::asio::ip::tcp::endpoint le = _acceptor.local_endpoint();
  _port = le.port();

  (void)f;
}

FTPServer::~FTPServer(void)
{
}

void FTPServer::open(void)
{
  accept();
}

void FTPServer::close(void)
{
  //std::clog << "shuting down FTP server ..." << std::endl;
  _coManager.closeAll();
  _acceptor.close();
  //std::clog << "FTP server shutdown success" << std::endl;
}

unsigned short FTPServer::getPort(void) const
{
  return (_port);
}

void FTPServer::accept(void)
{
  std::shared_ptr<FTPConnection> shc =
    std::make_shared<FTPConnection>(_io_service, _coManager, _pm, _filename);
  _acceptor.async_accept(shc->socket(),
			 boost::bind(&FTPServer::do_accept, this, shc,
				     boost::asio::placeholders::error));
}

bool FTPServer::inUse(void) const
{
  return (_inUse);
}

void FTPServer::setInUse(bool value)
{
  _inUse = value;
}

void FTPServer::setFilename(std::string const& fname)
{
  _filename = fname;
}

void FTPServer::do_accept(std::shared_ptr<FTPConnection> ptr,
			  boost::system::error_code const& ec)
{
  if (!ec) {
    _coManager.join(ptr);
    accept();
  }
  else {
    // std::clog << "error: ftp: accept: " << ec << ": " << ec.message() << std::endl;
  }
}
