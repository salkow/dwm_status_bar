#include <cstdio>
#include <fmt/core.h>
#include <string>

#include "updates.hpp"

int SetUpdates(Item* updates)
{
    FILE* fp = popen("checkupdates", "r");
	if (fp == nullptr)
	{
		updates->_is_active = false;
		return;
	}

	char ch;
	int num_of_updates = 0;

    // Get number of lines.
	while ((ch = getc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			num_of_updates++;
		}
	}

	pclose(fp);

	std::string old_value = updates->_value;

	if (num_of_updates == 0)
	{
		updates->_is_active = false;
	}

	else
	{
		updates->_value = fmt::format(" {}", num_of_updates);

		updates->_is_active = false;
	}

	return updates->_value != old_value;
}
