//
// Listen.cpp for server in /home/galibe_s/rendu/Spider/server/remote
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Nov  9 05:21:39 2016 stephane galibert
// Last update Wed Nov  9 05:46:03 2016 stephane galibert
//

#include "Listen.hpp"

Listen::Listen(boost::asio::io_service &ios, SSLSocket &socket)
  : _io_service(ios),
    _socket(socket),
    _signals(_io_service)
{
  _running = false;

  _signals.add(SIGINT);
  _signals.add(SIGTERM);
  _signals.add(SIGQUIT);

  signal();
}

Listen::~Listen(void)
{
}

void Listen::listen(void)
{
  _running = true;
  while (_running)
    {
      Packet const *reply = read();
      if (reply && reply->MAGIC == MAGIC_NUMBER) {
	std::cout << std::string(reply->data, reply->size) << std::flush;
      }
    }
}

/*void Listen::start(void)
{
  connect();
}

void Listen::close(void)
{
  // socket close
}

void Listen::init(void)
{
  try {
    _socket.set_verify_mode(boost::asio::ssl::verify_peer);
    _context.load_verify_file("server.crt");
  } catch (std::exception const& e) {
    std::cerr << "console init: " << e.what() << std::endl;
  }
}

void Listen::connect(void)
{
  try {
    boost::system::error_code error;
    boost::asio::ip::tcp::resolver::query q(_remoteIP, _remotePort);
    boost::asio::ip::tcp::resolver::iterator endpoint_it = _resolver.resolve(q);

    boost::asio::connect(_socket.lowest_layer(), endpoint_it, error);
    do_connect(error, endpoint_it);
  } catch (std::exception const& e) {
    throw (std::runtime_error(e.what()));
  }
}

void Listen::handshake(void)
{
  boost::system::error_code error;
  _socket.handshake(boost::asio::ssl::stream_base::client, error);
  do_handshake(error);
}

void Listen::do_connect(boost::system::error_code const& ec,
			 boost::asio::ip::tcp::resolver::iterator)
{
  if (!ec) {
    handshake();
  } else {
    std::cerr << "Error: " << _remoteIP << ":" << _remotePort
	      << " is inaccessible" << std::endl;
  }
}

void Listen::do_handshake(boost::system::error_code const& ec)
{
  if (!ec) {
    _running = true;
    listen();
  }
  else {
    std::clog << "Error: handshake failed" << std::endl;
  }
  }*/

Packet const *Listen::read(void)
{
  boost::system::error_code ec;
  size_t len;

  len = boost::asio::read(_socket, _read, boost::asio::transfer_at_least(sizeof(Packet)));
  if (ec) {
    throw (std::runtime_error(ec.message()));
  }

  Packet const *packet = boost::asio::buffer_cast<Packet const *>(_read.data());
  _read.consume(len);
  return (packet);
}

/*void Listen::write(Packet *packet)
{
  boost::system::error_code ec;
  boost::asio::write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size), ec);
  if (ec) {
    throw (std::runtime_error(ec.message()));
  }
  free(packet);
  }*/

void Listen::signal(void)
{
  _signals.async_wait(boost::bind(&Listen::do_signal, this,
				  boost::asio::placeholders::error,
				  boost::asio::placeholders::signal_number));
}

void Listen::do_signal(boost::system::error_code const& ec, int signo)
{
  if (!ec) {
    (void)signo;
    /*std::clog << std::endl << "receiving signal n°" << signo
      << " - skipped" << std::endl;*/
    //_io_service.stop();
    std::cout << "Exiting listen" << std::endl;
    _running = false;
  } else {
    std::clog << ec << std::endl;
  }
}
