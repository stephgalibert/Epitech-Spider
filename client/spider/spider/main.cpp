#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

#include "Application.h"

#include <Windows.h>
#include <shellapi.h>

int main(int ac, char **av);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	int w_argc = 0;
	int ret = 0;
	LPWSTR* w_argv = CommandLineToArgvW(GetCommandLineW(), &w_argc);
	if (w_argv)
	{
		std::vector<std::string> my_argv_buf;
		my_argv_buf.reserve(w_argc);

		for (int i = 0; i < w_argc; ++i)
		{
			int w_len = lstrlenW(w_argv[i]);
			int len = WideCharToMultiByte(CP_ACP, 0, w_argv[i], w_len, NULL, 0, NULL, NULL);
			std::string s;
			s.resize(len);
			WideCharToMultiByte(CP_ACP, 0, w_argv[i], w_len, &s[0], len, NULL, NULL);
			my_argv_buf.push_back(s.c_str());
		}

		std::vector<char *> my_argv;
		my_argv.reserve(my_argv_buf.size());
		for (std::vector<std::string>::iterator i = my_argv_buf.begin(); i != my_argv_buf.end(); ++i)
			my_argv.push_back((char *)i->c_str());

		ret = main(my_argv.size(), &my_argv[0]);

		LocalFree(w_argv);
	}
	return (ret);
}

int main(int ac, char **av)
{
	Application appli(av[0]);

	try {
		appli.init();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

	appli.loop();
	appli.close();

	return (0);
}