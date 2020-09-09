#include <stdlib.h>
#include <stdio.h>

#include "updates.h"

void SetUpdates(item* updates)
{
    FILE* fp = popen("checkupdates", "r");
	if (fp == NULL)
	{
		printf("checkupdate failed\n");
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

	if (num_of_updates == 0)
	{
		updates->is_active = 0;
	}

	else
	{
    	snprintf(updates->value, 10, " %d", num_of_updates);

		updates->is_active = 1;
	}
}
