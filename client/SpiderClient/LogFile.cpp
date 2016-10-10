#include "LogFile.h"

LogFile::LogFile(void)
	: _buf(_ofs), std::ostream(&_buf)
{
}

LogFile::~LogFile(void)
{
}

void LogFile::open(std::string const& filename)
{
	_filename = filename;
	_ofs.open(filename, std::ios::out | std::ios::app);
}

void LogFile::close(void)
{
	_ofs.close();
}
bool LogFile::isOpen(void) const
{
	return (_ofs.is_open());
}

std::string const& LogFile::getFilename(void) const
{
	return (_filename);
}

std::streamoff LogFile::getSize(void) const
{
	std::ifstream in(_filename.c_str(), std::ifstream::ate | std::ifstream::binary);
	return (in.tellg());
}

LogFile::LogBuf::LogBuf(std::ostream &out)
	: _out(out)
{
}

int LogFile::LogBuf::sync(void)
{
	_out << str();
	str("");
	_out.flush();
	return (0);
}
