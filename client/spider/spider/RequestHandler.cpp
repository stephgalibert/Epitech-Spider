#include "RequestHandler.h"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::request(IClient &client, Packet const* received, Packet **reply)
{
	if (received && received->type != PacketType::PT_Error && received->type != PacketType::PT_Response) {
		std::unique_ptr<IRequest> ptr(_builder.create(received->type));
		std::string param(received->data, received->size);
		if (ptr) {
			ptr->execute(client, param, reply);
		}
	}
}
