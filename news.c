#include <stdio.h>
#include <stdlib.h>

#include "news.h"

void SetNews(item* news)
{
    FILE* fp = popen("newsboat -C ~/.config/newsboat/config -x print-unread", "r");
	if (fp == NULL)
	{
		printf("newsboat failed\n");
	}

	int num_of_news = 0;

    fscanf(fp, "%d", &num_of_news);

	pclose(fp);

    if (num_of_news == 0)
    {
        news->is_active = 0;
    }

    else
    {
        snprintf(news->value, 10, "%d", num_of_news);

        news->is_active = 1;
    }
}
