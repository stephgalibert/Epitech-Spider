//
// UserInterface.cpp for server in /home/galibe_s/project/SpiderServer
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug  7 19:09:05 2016 stephane galibert
// Last update Mon Oct 24 12:52:13 2016 stephane galibert
//

#include "Console.hpp"

Console::Console(void)
  : _resolver(_io_service),
    _context(boost::asio::ssl::context::sslv23),
    _socket(_io_service, _context)
{
  /*_cmds["help"] = std::bind(&Console::cmd_help, this, std::placeholders::_1);
    _cmds["dump"] = std::bind(&Console::cmd_dump, this, std::placeholders::_1);*/
  _cmds["exit"] = std::bind(&Console::cmd_exit, this, std::placeholders::_1);
  /*_cmds["reload"] = std::bind(&Console::cmd_reload, this, std::placeholders::_1);
  _cmds["set"] = std::bind(&Console::cmd_set, this, std::placeholders::_1);
  _cmds["get"] = std::bind(&Console::cmd_get, this, std::placeholders::_1);
  _cmds["sql"] = std::bind(&Console::cmd_sql, this, std::placeholders::_1);*/

  _running = false;
}

Console::~Console(void)
{
}

void Console::start(void)
{
  connect();
  _th = std::thread(&Console::run, this);
}

void Console::close(void)
{
  _running = false;
  _io_service.stop();
  if (_th.joinable()) {
    _th.join();
  }
  if (_ui.joinable()) {
    _ui.join();
  }
}

PluginInfo const& Console::getPluginInfo(void) const
{
  return (g_info);
}

void Console::init(void)
{
  try {
    _socket.set_verify_mode(boost::asio::ssl::verify_peer);
    //_socket.set_verify_callback(boost::bind(&Console::verify_crt, this, _1, _2));
    _context.load_verify_file("certificates/server.crt");
  } catch (std::exception const& e) {
    std::cerr << "console init: " << e.what() << std::endl;
  }
}

void Console::run(void)
{
  try {
    _io_service.run();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Console::input(void)
{
  std::vector<std::string> av;
  std::string line;

  std::cout << StaticTools::GetHour() << " $> ";
  while (_running && std::getline(std::cin, line))
    {
      if (line.size() > 0) {
	boost::trim_if(line, boost::is_any_of(" \t"));
	boost::split(av, line, boost::is_any_of(" \t"), boost::token_compress_on);

	if (_cmds.find(av[0]) != _cmds.cend())
	  _cmds.at(av[0])(av);
	else
	  std::clog << av[0] << ": Unknown command" << std::endl;
      }
      av.clear();
      if (_running) {
	std::cout << StaticTools::GetHour() << " $> ";
      }
    }
}

void Console::connect(void)
{
  boost::asio::ip::tcp::resolver::query q("localhost",
					  boost::lexical_cast<std::string>(4242));
  boost::asio::ip::tcp::resolver::iterator endpoint_it = _resolver.resolve(q);
  boost::asio::async_connect(_socket.lowest_layer(), endpoint_it,
			     boost::bind(&Console::do_connect, this,
					 boost::asio::placeholders::error,
					 boost::asio::placeholders::iterator));
}

void Console::handshake(void)
{
  _socket.async_handshake(boost::asio::ssl::stream_base::client,
			  boost::bind(&Console::do_handshake, this,
				      boost::asio::placeholders::error));
}

void Console::do_connect(boost::system::error_code const& ec,
			 boost::asio::ip::tcp::resolver::iterator)
{
  if (!ec) {
    handshake();
  } else {
    std::cerr << "Error on loading UIConsole plugin" << std::endl;
  }
}

void Console::do_handshake(boost::system::error_code const& ec)
{
  if (!ec) {
    _running = true;
    _ui = std::thread(&Console::input, this);
  }
  else {
    std::clog << "UIConsole: handshake FAILED" << std::endl;
  }
}

bool Console::verify_crt(bool preverified, boost::asio::ssl::verify_context& ctx)
{
  char name[256];

  X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
  X509_NAME_oneline(X509_get_subject_name(cert), name, 256);
  std::cout << "veryfing " << name << std::endl;
  return (preverified);
}

Packet *Console::read(void)
{
  boost::system::error_code ec;
  boost::array<char, 1024> buf;

  _socket.read_some(boost::asio::buffer(buf), ec);
  if (ec) {
    throw (std::runtime_error(ec.message()));
  }
  return (reinterpret_cast<Packet *>(buf.data()));
}

void Console::write(Packet *packet)
{
  boost::system::error_code ec;
  boost::asio::write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size), ec);
  if (ec) {
    throw (std::runtime_error(ec.message()));
  }
  free(packet);
}

/*void Console::cmd_help(std::vector<std::string> const& av)
{
  JSONBuilder builder;
  JSONReader reader;
  std::string type;
  std::vector<std::pair<std::string, std::string> > result;

  builder.addValue("type", "cmd");
  builder.addValue("name", av[0]);

  try {
    write(builder.get());
    reader.readFromString(read());
    type = reader.getValue<std::string>("type");
    if (type == "result") {
      reader.getListValues("data", result);
      for (auto &it : result) {
	std::cout << it.first << " : " << it.second << std::endl;
      }
    }
    else if (type == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    }
  } catch (std::exception const& e) {
    std::cerr << "UIConsole: help: " << e.what() << std::endl;
  }
}

void Console::cmd_dump(std::vector<std::string> const& av)
{
  JSONBuilder builder;
  JSONReader reader;
  std::string type;
  std::vector<std::vector<std::pair<std::string, std::string> > > result;

  builder.addValue("type", "cmd");
  builder.addValue("name", av[0]);
  builder.addListValues("param", av);

  try {
    write(builder.get());
    reader.readFromString(read());
    type = reader.getValue<std::string>("type");
    if (type == "result") {
      reader.getArrayValues("data", result);
      for (auto &it : result) {
	std::cout << "---------------------------------" << std::endl;
	for (auto &subit : it) {
	  std::cout << subit.first << ": " << subit.second << std::endl;
	}
      }
      std::cout << "---------------------------------" << std::endl;
    }
    else if (type == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    }
  } catch (std::exception const& e) {
    std::cerr << "UIConsole: " << e.what() << std::endl;
  }

  }*/

void Console::cmd_exit(std::vector<std::string> const& av)
{
  size_t i = 0;
  Packet *packet;
  std::string data = av[0];

  packet = (Packet *)malloc(sizeof(Packet) + (av[0].size() * sizeof(char) + 1));
  packet->size = av[0].size();
  packet->type = PacketType::PT_Kill;
  while (i < av[0].size()) {
    packet->data[i] = av[0][i];
    ++i;
  }
  packet->data[i] = 0;

  std::cout << "Console: write type: " << (int)packet->type
	    << " data: " << std::string(packet->data, packet->size) << std::endl;

  try {
    write(packet);
    Packet *reply = read();

    std::cout << "Console: read type: " << (int)packet->type
	      << " data: " << std::string(packet->data, packet->size) << std::endl;

    if (reply && reply->type == PacketType::PT_Response) {
      std::string data(reply->data, reply->size);
      std::cerr << data << std::endl;
    }
    else {
      _running = false;
    }
  } catch (std::exception const& e) {
    std::cerr << "uiconsole: exit: " << e.what() << std::endl;
  }

  /*try {
    write(builder.get());
    reader.readFromString(read());
    if (reader.getValue<std::string>("type") == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    } else {
      _running = false;
    }
  } catch (std::exception const& e) {
    //std::cerr << "UIConsole: exit: " << e.what() << std::endl;
    }*/
}

/*void Console::cmd_reload(std::vector<std::string> const& av)
{
  JSONBuilder builder;
  JSONReader reader;
  std::string type;

  builder.addValue("type", "cmd");
  builder.addValue("name", av[0]);
  builder.addListValues("param", av);

  try {
    write(builder.get());
    reader.readFromString(read());
    if (reader.getValue<std::string>("type") == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    }
  } catch (std::exception const& e) {
    std::cerr << "UIConsole: reload: " << e.what() << std::endl;
  }
}

void Console::cmd_set(std::vector<std::string> const& av)
{
  JSONBuilder builder;
  JSONReader reader;

  builder.addValue("type", "cmd");
  builder.addValue("name", av[0]);
  builder.addListValues("param", av);

  try {
    write(builder.get());
    reader.readFromString(read());
    if (reader.getValue<std::string>("type") == "error")
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    else
      std::cerr << reader.getValue<std::string>("data") << std::endl;

  } catch (std::exception const& e) {
    std::cerr << "UIConsole: set: " << e.what() << std::endl;
  }
}

void Console::cmd_get(std::vector<std::string> const& av)
{
  std::vector<std::pair<std::string, std::string> > result;
  JSONBuilder builder;
  JSONReader reader;

  builder.addValue("type", "cmd");
  builder.addValue("name", av[0]);
  builder.addListValues("param", av);

  try {
    write(builder.get());
    reader.readFromString(read());
    if (reader.getValue<std::string>("type") == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    }
    else {
      reader.getListValues("data", result);
      for (auto &it : result) {
	std::cout << it.first << ": " << it.second << std::endl;
      }
    }
  } catch (std::exception const& e) {
    std::cerr << "UIConsole: get: " << e.what() << std::endl;
  }
}

void Console::cmd_sql(std::vector<std::string> const& av)
{
  std::vector<std::vector<std::pair<std::string, std::string> > > result;
  std::vector<std::string> tmp;
  std::vector<std::string> params;
  JSONBuilder builder;
  JSONReader reader;
  std::string type;
  std::string stmt;

  tmp.insert(tmp.begin(), av.begin() + 1, av.end());
  params.push_back("sql");
  params.push_back(boost::algorithm::join(tmp, " "));

  builder.addValue("type", "cmd");
  builder.addValue("name", params[0]);
  builder.addListValues("param", params);

  try {
    write(builder.get());
    reader.readFromString(read());
    type = reader.getValue<std::string>("type");
    if (type == "result") {
      reader.getArrayValues("data", result);

      for (auto &it : result) {
	std::cout << "---------------------------------" << std::endl;
	for (auto &subit : it) {
	  std::cout << subit.first << ": " << subit.second << std::endl;
	}
      }
      std::cout << "---------------------------------" << std::endl;
    }
    else if (type == "error") {
      std::cerr << reader.getValue<std::string>("name") << std::endl;
    }

  } catch (std::exception const& e) {
    std::cerr << "UIConsole: get: " << e.what() << std::endl;
  }
  }*/
