#include "updates.hpp"
#include "../config.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

Updates::Updates(ItemData* data, int signal)
	: Item(data, signal) {}

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

void Updates::Clicked(int button)
{
	if (button == 1)
	{
		system(fmt::format("setsid -f {0} -t Updates -e {1} -c 'yay -Syu && {1}'", TERMINAL, SHELL).c_str());
	}
}
