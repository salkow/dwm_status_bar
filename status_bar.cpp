#include "status_bar.hpp"
#include "config.hpp"

#include <sstream>
#include <exception>
#include <unistd.h>
#include <X11/Xlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <fcntl.h>
#include <iostream>

StatusBar::StatusBar()
{
	is_running_ = true;

	CreateItems();

	read_fifo_thread_ = std::thread(&StatusBar::ReadFifo, this);

    for (auto i = items_.begin(); i != items_.end(); ++i) 
	{
		if ((*i)->default_update_interval_ == 0)
		{
			(*i)->update_interval_ = -1;
		}

		else
		{
			// 0, to update immediately when it starts.
			(*i)->update_interval_ = 0;
		}

		if ((*i)->has_event_handler_ == true)
		{
			std::thread event_handler(&Item::UpdateWhenEvent, (*i));
			event_handler.detach();
		}
	}
}

StatusBar::~StatusBar()
{
	read_fifo_thread_.join();

    for (auto i = items_.begin(); i != items_.end(); ++i) 
	{
		delete (*i);
	}
}

void StatusBar::SetRoot()
{
	root_mutex_.lock();

	Display* display = XOpenDisplay(NULL);

	int screen = DefaultScreen(display);
	Window root = RootWindow(display, screen);
	XStoreName(display, root, status_bar_str_.c_str());

	XCloseDisplay(display);

	root_mutex_.unlock();
}

void StatusBar::SetValue()
{
	std::ostringstream status_bar_stream;

    for (auto i = items_.begin(); i != items_.end(); ++i) 
	{
		if ((*i)->is_active_ == 1)
		{
			status_bar_stream << ' ' << (*i)->value_ << " " << DELIM_CHARACTER;
		}
	}

	// Remove the last | character.
	status_bar_str_ = status_bar_stream.str();
	status_bar_str_.pop_back();
}

void StatusBar::Start()
{
	while (is_running_)
	{
		int has_changed = 0;

    	for (auto i = items_.begin(); i != items_.end(); ++i) 
		{
			if ((*i)->update_interval_ != -1)
			{
				(*i)->update_interval_ -= UPDATE_INTERVAL;	

				if ((*i)->update_interval_ <= 0)
				{
					has_changed += (*i)->SetValue();
					(*i)->update_interval_ = (*i)->default_update_interval_;
				}
			}
		}

		if (has_changed)
		{
			SetValue();
			SetRoot();
		}

		sleep(UPDATE_INTERVAL);
	}
}

void StatusBar::ReadFifo()
{
	int my_fd;

	remove(FIFO_FILE);

	mkfifo(FIFO_FILE, 0666);

	char signal[4];

	while (is_running_)
	{
		my_fd = open(FIFO_FILE, O_RDONLY);

		read(my_fd, &signal, 4);

		int signal_origin = signal[0] - '0';

		// Convert char to int.
		int signal_int = atoi(&(signal[1]));

		if (signal_origin == 0)
		{
			bool changed = items_[signal_int]->SetValue();

			if (changed)
			{
				SetValue();
				SetRoot();
			}
		}

		else
		{
			int pos = signal_int;

			// We want to filter out the inactive items.
			for (auto i = items_.begin(); i != items_.end(); ++i)
			{
				if ((*i)->is_active_ == true)
				{
					if (pos == 0 && (*i)->has_clicked_ == true)
					{
						(*i)->Clicked(signal_origin);
					}

					pos--;
				}
			}
		}

		close(my_fd);
	}
}

void StatusBar::CreateItems()
{
	int num_of_items = sizeof(items_data) / sizeof(ItemData);

	for (int i = 0; i < num_of_items; i++)
	{
		items_.push_back(items_data[i].CreateInstancePtr(items_data[i].name, items_data[i].update_interval,
											  			 items_data[i].has_event_handler,
														 items_data[i].has_click_event));
	}

	items_.shrink_to_fit();
}
