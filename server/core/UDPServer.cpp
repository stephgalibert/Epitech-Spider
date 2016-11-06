//
// UDPServer.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:57:31 2016 stephane galibert
// Last update Sun Nov  6 18:37:55 2016 stephane galibert
//

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_service &io_service, int port,
		     RequestHandler &req, ServerConfig &config, PluginManager &pm)
  : AServer(io_service, port, req, config, pm)
    //_connection(io_service, req, pm, config, port)
    //_socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    //_running(false)
{
  _connection = std::make_shared<UDPConnection>(io_service, req, pm, config, port);
}

UDPServer::~UDPServer(void)
{
}

void UDPServer::init(void)
{
  /*try {

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    }*/
}

void UDPServer::open(void)
{
  /*try {
    _running = true;
    receive();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    }*/
  _connection->start();
}

void UDPServer::close(void)
{
  //_running = false;
  std::clog << "shuting down UDP server ..." << std::endl;
  std::clog << "UDP server shutdown success" << std::endl;
}

/*void UDPServer::write(Packet *data)
{
  bool write_in_progress = !_toWrites.empty();

  _toWrites.push(data);
  if (!write_in_progress) {
    write();
  }
}

void UDPServer::receive(void)
{
  _socket.async_receive_from(_read.prepare(2048), _endpoint,
			     boost::bind(&UDPServer::do_receive, this,
					 boost::asio::placeholders::error,
					 boost::asio::placeholders::bytes_transferred));
					 }*/

/*void UDPServer::do_receive(boost::system::error_code const& ec, size_t)
{
  if (!ec || ec == boost::asio::error::message_size) {
    Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
    _read.consume(sizeof(Packet) + (packet->size * sizeof(char)));

    if (packet && packet->MAGIC == MAGIC_NUMBER) {
      std::cout << "udp receive: " << std::string(packet->data, packet->size) << std::endl;
      write(StaticTools::CreatePacket(PacketType::PT_Response, "success"));
    } else {
      write(StaticTools::CreatePacket(PacketType::PT_Error, "error"));
      }*/

    /*Packet *reply = NULL;
    _reqHandler.request(shared_from_this(), packet, &reply);

    if (reply) {
      write(reply);
      }*/

/*if (_running) {
      receive();
    }
  }
  }*/

/*void UDPServer::write(void)
{
  Packet *packet = _toWrites.front();
  _socket.async_send_to(boost::asio::buffer(packet, sizeof(Packet) + packet->size),
			_endpoint,
			boost::bind(&UDPServer::do_write, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
}

void UDPServer::do_write(boost::system::error_code const& ec, size_t)
{
  if (!ec) {

    Packet *packet = _toWrites.front();
    free(packet);

    _toWrites.pop();

    if (!_toWrites.empty()) {
      write();
    }
  }
  }*/
