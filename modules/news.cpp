#include "news.hpp"
#include "../config.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

News::News(ItemData* data, int signal)
    : Item(data, signal){}

int News::SetValue()
{
    FILE* fp = popen("newsboat -x print-unread", "r");
	if (fp == nullptr)
	{
        is_active_ = false;
		return 1;
	}

	int num_of_news = 0;

    fscanf(fp, "%d", &num_of_news);

	pclose(fp);

    std::string old_value = value_;

    if (num_of_news == 0)
    {
        is_active_ = false;
		return 1;
    }

    else
    {
        value_ = fmt::format("📰 {}", num_of_news);

        is_active_ = true;
    }

    return value_ != old_value;
}

void News::Clicked(int button)
{
    if (button == 1)
    {
		system(fmt::format("setsid -f {0} -t newsboat -e {1} -c 'newsboat -C /home/salkow/.config/newsboat/config -u /home/salkow/.config/newsboat/urls && {1}'", TERMINAL, SHELL).c_str());

        // Signal application to update the number of unread news.
        char status_bar_signal[4];
        snprintf(status_bar_signal, 4, "%03d", signal_);

        int fd = open(FIFO_FILE, O_WRONLY | O_NONBLOCK);
        write(fd, status_bar_signal, 4);
        close(fd);
    }
}
