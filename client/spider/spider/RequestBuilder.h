//
// RequestBuilder.hpp for server in /home/galibe_s/project/SpiderServer/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Aug 18 13:24:38 2016 stephane galibert
// Last update Sun Aug 21 22:12:41 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

#include "Protocol.h"

#include "IRequest.h"
#include "Kill.h"
#include "Stealer.h"

class RequestBuilder : private boost::noncopyable
{
public:
	typedef std::function<std::unique_ptr<IRequest>(void)> Cmds;
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> create(PacketType type) const;
private:
	std::unique_ptr<IRequest> kill(void) const;
	std::unique_ptr<IRequest> stealer(void) const;

	std::unordered_map<PacketType, Cmds> _cmds;
};
