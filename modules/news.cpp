#include <cstdio>
#include <fmt/core.h>
#include <string>

#include "news.hpp"

int SetNews(Item* news)
{
    FILE* fp = popen("newsboat -x print-unread", "r");
	if (fp == nullptr)
	{
        news->_is_active = false;
		return;
	}

	int num_of_news = 0;

    fscanf(fp, "%d", &num_of_news);

	pclose(fp);

    std::string old_value = news->_value;

    if (num_of_news == 0)
    {
        news->_is_active = false;
    }

    else
    {
        news->_value = fmt::format("{}", num_of_news);

        news->_is_active = true;
    }

    return news->_value != old_value;
}
