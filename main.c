#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "dwmbar.h"

int main()
{
	int num_of_items = sizeof(status_bar_items) / sizeof(item);

	int i;

	int time_to_update[num_of_items];

	for (i = 0; i < num_of_items; i++)
	{
		// We need this, to support items with no update period.
		if (status_bar_items[i].update_period == 0)
		{
			time_to_update[i] = -1;
		}

		else
		{
			time_to_update[i] = status_bar_items[i].update_period; 
		}
	}

	char *status_bar = malloc(100);
	int changed = 0;

	while (1)
	{
		for (i = 0; i < num_of_items; i++)
		{
			if (time_to_update[i] == 0)
			{
				status_bar_items[i].SetValue(&(status_bar_items[i]));
				changed += time_to_update[i] = status_bar_items[i].update_period;
			}

			else if (time_to_update[i] != -1)
			{
				(time_to_update[i])--;	
			}
		}

		if (changed)
		{
			SetStatusBar(status_bar_items, num_of_items, status_bar);

			SetRoot(status_bar);

			changed = 0;
		}

		sleep(60);
	}

	return 0;	
}
