#include "news.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

News::News(int update_interval, bool has_event_handler, bool needs_internet,
           bool has_clicked)
    : Item(update_interval, has_event_handler, needs_internet, has_clicked) {}

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
        system("setsid -f newsboat -C /home/salkow/.config/newsboat/config -u /home/salkow/.config/newsboat/urls >/dev/null 2>&1");

        // Signal application to update the number of unread news.
        char status_bar_signal[4];
        snprintf(status_bar_signal, 4, "%03d", signal_);

        int fd = open("/home/salkow/Projects/dwm_status_bar/update_fifo", O_WRONLY | O_NONBLOCK);
        write(fd, status_bar_signal, 4);
        close(fd);
    }
}
