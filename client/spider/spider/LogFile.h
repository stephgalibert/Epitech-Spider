#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "StaticTools.h"

class LogFile : public std::ostream
{
public:
	LogFile(void);
	~LogFile(void);

	void open(std::string const& filename);
	void close(void);

	bool isOpen(void) const;
	std::string const& getFilename(void) const;
	std::streamoff getSize(void) const;

protected:
	class LogBuf : public std::stringbuf
	{
	public:
		LogBuf(std::ostream &out);
		virtual int sync(void);
	private:
		std::ostream &_out;
	};

	LogBuf _buf;

	std::ofstream _ofs;
	std::string _filename;
};