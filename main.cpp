#include "status_bar.hpp"
#include "util.hpp"

#include <iostream>

int main()
{
	if (IsAlreadyRunning())
	{
		std::cout << "Another instance is running.\n" << 
					 "If you are sure that it is not, delete the file: /tmp/dwm_status_bar.pid.\n";


		return 1;
	}

	StatusBar status_bar;

	status_bar.Start();

	return 0;
}
