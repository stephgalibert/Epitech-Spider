#include "RequestBuilder.h"

RequestBuilder::RequestBuilder(void)
{
  _cmds["kill"] = std::bind(&RequestBuilder::kill, this);
}

RequestBuilder::~RequestBuilder(void)
{
}

std::unique_ptr<IRequest> RequestBuilder::create(std::string const& name) const
{
  if (_cmds.find(name) != _cmds.cend()) {
    return (std::move(_cmds.at(name)()));
  }
  return (NULL);
}

std::unique_ptr<IRequest> RequestBuilder::kill(void) const
{
  return (std::unique_ptr<IRequest>(new Kill));
}