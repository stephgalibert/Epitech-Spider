#include "RequestHandler.h"
#include "TCPClient.h"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

std::string RequestHandler::request(IClient &client, std::string const& data)
{
  try {
    JSONReader reader;
    std::string type;

    reader.readFromString(data);
    type = reader.getValue<std::string>("type");
    if (type == "cmd") {
      return (cmd(client, reader));
    }
	else if (type == "result" || type == "error") {
		return ("");
	}

    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", type + ": Unknown type");
    return (builder.get());

  } catch (std::exception const& e) {
	(void)e;
	JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", "Bad JSON");
    return (builder.get());
  }
}

std::string RequestHandler::cmd(IClient &client, JSONReader &reader)
{
  std::string ret;

  try {
    std::string name = reader.getValue<std::string>("name");
    std::unique_ptr<IRequest> ptr(_builder.create(name));

    if (!ptr) {
      JSONBuilder builder;
      builder.addValue("type", "error");
      builder.addValue("name", name + ": Unknown command");
      ret = builder.get();
    }
    else {
      ret = ptr->execute(client, reader);
    }

  } catch (std::exception const& e) {
	(void)e;
    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", "bad JSON");
    ret = builder.get();
  }
  return (ret);
}
