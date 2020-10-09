#include "updates.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

Updates::Updates(int update_interval, int signal, bool has_event_handler, 
				 bool needs_internet, bool has_clicked)
    : Item(update_interval, signal, has_event_handler, needs_internet, has_clicked) {}

int Updates::SetValue()
{
    FILE* fp = popen("checkupdates", "r");
	if (fp == nullptr)
	{
		is_active_ = false;
		return 1;
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

	std::string old_value = value_;

	if (num_of_updates == 0)
	{
		is_active_ = false;
	}

	else
	{
		value_ = fmt::format("📥 {}", num_of_updates);

		is_active_ = true;
	}

	return value_ != old_value;
}
