//
// RequestHandler.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:04:39 2016 stephane galibert
// Last update Wed Aug 24 22:26:52 2016 stephane galibert
//

#include "RequestHandler.hpp"

RequestHandler::RequestHandler(void)
{
}

RequestHandler::~RequestHandler(void)
{
}

std::string RequestHandler::request(AConnection::shared own, std::string const& data)
{
  try {
    JSONReader reader;
    std::string type;

    reader.readFromString(data);
    type = reader.getValue<std::string>("type");
    if (type == "cmd") {
      return (cmd(own, reader));
    }
    else if (type == "result" || type == "error") {
      return ("");
    }

    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", type + ": Unknown type");
    return (builder.get());

  } catch (std::exception const& e) {
    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", "Bad JSON");
    return (builder.get());
  }
}

std::string RequestHandler::cmd(AConnection::shared own, JSONReader &reader)
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
      ret = ptr->execute(own, reader);
    }

  } catch (std::exception const& e) {
    JSONBuilder builder;
    builder.addValue("type", "error");
    builder.addValue("name", "bad JSON");
    ret = builder.get();
  }
  return (ret);
}

/*std::string RequestHandler::cmd_key(AConnection::shared own, JSONReader &reader)
{
  JSONBuilder builder;

  if (av.size() > 1 && own->isEnabled()) {
    //own->writeLog(av[1]);
    builder.addValue("type", "cmd");
    builder.addValue("name", "OK");
    return (builder.get());
  }
  builder.addValue("type", "error");
  builder.addValue("data", "not registered");
  return (builder.get());
  (void)own;
  (void)reader;
  return ("KO");
  }*/
