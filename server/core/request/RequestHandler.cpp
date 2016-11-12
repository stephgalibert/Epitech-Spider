//
// RequestHandler.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:39 2016 stephane galibert
// Last update Sat Nov 12 19:58:06 2016 stephane galibert
//

#include "RequestHandler.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::request(AConnection::shared own, Packet const* received,
			     Packet **reply)
{
  std::unique_ptr<IRequest> ptr;

  if (received && received->type != PacketType::PT_Response
      && received->type != PacketType::PT_Error) {
    if (received->MAGIC == MAGIC_NUMBER) {

      if (received->type == PacketType::PT_Command) {
	createCmd(own, received, reply);
      }
      else {
	createReq(own, received, reply);
      }
    }
    else {
      *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_DATA);
    }
  }
}

void RequestHandler::createReq(AConnection::shared own, Packet const *received,
			       Packet **reply)
{
  std::unique_ptr<IRequest> ptr(_reqBuilder.create(received->type));

  if (ptr) {
    std::string param(received->data, received->size);
    ptr->execute(own, param, reply);
  } else {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_CMD);
  }
}

void RequestHandler::createCmd(AConnection::shared own, Packet const *received,
			       Packet **reply)
{
  std::string name;
  JSONReader reader;
  std::string data(received->data, received->size);

  try {
    reader.readFromString(data);
    name = reader.getValue<std::string>("name");

    std::unique_ptr<ICommand> ptr(_cmdBuilder.create(name));
    if (ptr) {
      ptr->execute(own, reader, reply);
    } else {
      *reply = StaticTools::CreatePacket(PacketType::PT_Error, BAD_CMD);
    }
  } catch (std::exception const& e) {
    *reply = StaticTools::CreatePacket(PacketType::PT_Error, ERROR_JSON);
  }
}
