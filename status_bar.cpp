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

using namespace std;

StatusBar::StatusBar()
{
	is_running_ = true;

	CreateItems();

	read_fifo_thread_ = std::thread(&StatusBar::ReadFifo, this);

    for (auto i = items_.begin(); i != items_.end(); ++i) 
	{
		if ((*i)->default_update_interval_ == 0)
		{
			(*i)->data_->update_interval_ = -1;
		}

		else
		{
			// 0, to update immediately when it starts.
			(*i)->data_->update_interval_ = 0;
		}

		if ((*i)->data_->has_event_handler_ == true)
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
			if ((*i)->data_->update_interval_ != -1)
			{
				(*i)->data_->update_interval_ -= UPDATE_INTERVAL;	

				if ((*i)->data_->update_interval_ <= 0)
				{
					has_changed += (*i)->SetValue();

					(*i)->data_->update_interval_ = (*i)->default_update_interval_;
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
					if (pos == 0 && (*i)->data_->has_clicked_ == true)
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
	int num_of_items = sizeof(item_data) / sizeof(ItemData);

	for (int i = 0; i < num_of_items; i++)
	{
		items_.push_back(item_data[i].CreateInstancePtr_(&(item_data[i]), i));
	}

	items_.shrink_to_fit();
}
