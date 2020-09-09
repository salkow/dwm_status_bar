#include <stdlib.h>

#include "config.h"
#include "dwmbar.h"

int main()
{
	int num_of_items = sizeof(status_bar_items) / sizeof(item);

	int i;

	for (i = 0; i < num_of_items; i++)
	{
		status_bar_items[i].SetValue(&(status_bar_items[i]));
	}

	char *status_bar = malloc(100);

	SetStatusBar(status_bar_items, num_of_items, status_bar);

	SetRoot(status_bar);

	return 0;	
}
