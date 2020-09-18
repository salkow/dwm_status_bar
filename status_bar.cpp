#include <sstream>
#include <unistd.h>
#include <X11/Xlib.h>

#include "status_bar.hpp"
#include "config.hpp"

StatusBar::StatusBar()
{
	_num_of_items = sizeof(status_bar_items_conf) / sizeof(ConfItem);

	_items = new Item[_num_of_items];	

	for (int i = 0; i < _num_of_items; i++)
	{
		_items[i] = Item(status_bar_items_conf[i].icon,
						status_bar_items_conf[i].update_interval,
						status_bar_items_conf[i].signal,
						status_bar_items_conf[i].SetValue);

		// We need this, to support items with no update period.
		if (_items[i]._update_interval == 0)
		{
			_items[i]._update_interval = -1;
		}

        else
        {
			// 0, to update immediately when it starts.
			_items[i]._update_interval = 0;
        }
	}	
}

void StatusBar::SetRoot()
{
	Display* display = XOpenDisplay(NULL);

	int screen = DefaultScreen(display);
	Window root = RootWindow(display, screen);
	XStoreName(display, root, _status_bar_str.c_str());
	XCloseDisplay(display);
}

void StatusBar::SetValue()
{
	std::ostringstream status_bar_stream;

	for (int i = 0; i < _num_of_items; i++)
	{
		if (_items[i]._is_active == 1)
		{
			status_bar_stream << ' ' << _items[i]._icon << _items[i]._value << " |";
		}
	}

	// Remove the last | character.
	_status_bar_str = status_bar_stream.str();
	_status_bar_str.pop_back();
}

void StatusBar::Start()
{
	while (1)
	{
		for (int i = 0; i < _num_of_items; i++)
		{
			if (_items[i]._update_interval != -1)
			{
				_items[i]._update_interval -= UPDATE_INTERVAL;	

				if (_items[i]._update_interval <= 0)
				{
					_items[i]._SetValue(&(_items[i]));
					_items[i]._update_interval = status_bar_items_conf[i].update_interval;
				}
			}
		}

		SetValue();
		SetRoot();

		sleep(UPDATE_INTERVAL);
	}
}
