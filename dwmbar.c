#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

#include "dwmbar.h"

static int screen;
static Window root;
static Display *dpy;

void SetRoot(char* status_bar_str)
{
	Display* d = XOpenDisplay(NULL);
	if (d) 
	{
		dpy = d;
	}

	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);
	XStoreName(dpy, root, status_bar_str);
	XCloseDisplay(dpy);
}

void SetStatusBar(item* items, int num_of_items, char* status_bar)
{
	int i;
	int pos = 0;

	for (i = num_of_items - 1; i >= 0 ; i--)
	{
		if (items[i].is_active == 1)
		{
			status_bar[pos++] = ' ';
			strcpy(&(status_bar[pos]), items[i].icon);
			pos += strlen(items[i].icon);

			strcpy(&(status_bar[pos]), items[i].value);
			pos += strlen(items[i].value);

			strcpy(&(status_bar[pos]), " |");
			pos += 2;
		}
	}

	status_bar[pos - 1] = '\0';
}