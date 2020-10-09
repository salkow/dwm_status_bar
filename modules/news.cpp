#include "news.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

News::News(int update_interval, int signal, bool has_event_handler,
		   bool needs_internet, bool has_clicked)
    : Item(update_interval, signal, has_event_handler, needs_internet, has_clicked) {}

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
