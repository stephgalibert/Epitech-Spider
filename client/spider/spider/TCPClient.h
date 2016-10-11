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

#include "StaticTools.h"
#include "RequestHandler.h"

class TCPClient
{
public:
	TCPClient(void);
	~TCPClient(void);

	void connect(std::string const& remote, std::string const& port);
	void write(std::string const& data);
	void disconnect(void);

	void run(void);

	bool isConnected(void) const;

	TCPClient &operator<<(std::string const& data);
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
	std::queue<std::string> _toWrites;
	std::string _remote;
	std::string _port;
	bool _connected;
	RequestHandler _reqHandler;

	std::thread _runThread;
	std::ofstream _ofs;
};

