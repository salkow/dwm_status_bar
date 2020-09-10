#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "updates.h"

int SetUpdates(item* updates)
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

	// Check if the old value is same as the new.
	char old_updates_value[50];
	strcpy(old_updates_value, &(updates->value[sizeof(updates->icon)]));

	if (strcmp(old_updates_value, updates->value) == 0)
	{
		return 0;
	}

	else 
	{
		return 1;
	}
}
