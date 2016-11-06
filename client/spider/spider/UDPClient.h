#pragma once

#include <string>
#include <thread>
#include <deque>
#include <queue>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <string.h>

#include "IClient.h"
#include "StaticTools.h"
#include "RequestHandler.h"

class UDPClient : public IClient
{
 public:
	UDPClient(std::string const& ip, std::string const& port);
	virtual ~UDPClient(void);

	virtual void connect(void);
	virtual void write(Packet* packet);
	virtual void disconnect(void);
	virtual void run(void);
	virtual bool isConnected(void) const;
	virtual IClient &operator<<(Packet *packet);
	virtual Packet *createPacket(PacketType type, std::string const& data);

 private:
	 void do_write(boost::system::error_code const& ec, size_t);
	 void do_read(boost::system::error_code const& ec, size_t);

	 void runThread(void);
	 void write(void);
	 void read(void);

	 boost::asio::io_service _io_service;
	 boost::asio::ip::udp::udp::resolver _resolver;
	 boost::asio::ip::udp::udp::socket _socket;
	 boost::asio::ip::udp::endpoint _sender;

	 std::queue<Packet *> _toWrites;
	 //std::deque<Packet *> _toWrites;
	 boost::asio::streambuf _read;
	 RequestHandler _reqHandler;

	 std::thread _runThread;
	 bool _connected;

	 std::string _remote;
	 std::string _port;

	 std::ofstream _debug;
};

