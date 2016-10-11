//
// UDPServer.cpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 09:32:37 2016 stephane galibert
// Last update Wed Aug 17 15:35:47 2016 stephane galibert
//

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_service &io_service, int port)
  : AServer(io_service, port),
    _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{

}

UDPServer::~UDPServer(void)
{
}

void UDPServer::init(void)
{
  try {

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void UDPServer::open(void)
{
  try {
    receive();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void UDPServer::close(void)
{
  std::clog << "shuting down UDP server ..." << std::endl;

  std::clog << "UDP server shutdown success" << std::endl;
}

void UDPServer::write(std::string const& data)
{
  bool write_in_progress = !_toWrites.empty();
  _toWrites.push(data);
  if (!write_in_progress) {
    write();
  }
}

void UDPServer::receive(void)
{
  _socket.async_receive_from(boost::asio::buffer(_recv_buffer), _endpoint,
			     boost::bind(&UDPServer::do_receive, this,
					 boost::asio::placeholders::error,
					 boost::asio::placeholders::bytes_transferred));
}

void UDPServer::do_receive(boost::system::error_code const& ec, size_t)
{
  if (!ec || ec == boost::asio::error::message_size) {
    write("connected");
    receive();
  }
}

void UDPServer::write(void)
{
  _socket.async_send_to(boost::asio::buffer(_toWrites.front()), _endpoint,
			boost::bind(&UDPServer::do_write, this));
}

void UDPServer::do_write(void)
{
  _toWrites.pop();
  if (!_toWrites.empty()) {
    write();
  }
}
