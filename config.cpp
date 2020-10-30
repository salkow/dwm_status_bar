#include "modules/mpd.hpp"
#include "modules/news.hpp"
#include "modules/updates.hpp"
#include "modules/temp.hpp"
#include "modules/keyboard_language.hpp"
#include "modules/weather.hpp"
#include "modules/volume.hpp"
#include "modules/date.hpp"
#include "modules/task.hpp"

#include "status_bar.hpp"

void StatusBar::CreateItems()
{
    update_interval_ = 10;
	delim_character_ = '|';
	strcpy(fifo_file_, "/home/salkow/Projects/dwm_status_bar/update_fifo");

	// Update interval, has event handler, has click event

	items_.push_back(new Mpd(3600, 1, 1));
	items_.push_back(new News(3600, 0, 1));
	items_.push_back(new Task(1800, 0, 1));
	// items_.push_back(new Updates(10, 1));
	items_.push_back(new Temp(60, 0, 0));
	items_.push_back(new KeyboardLanguage(3600, 1, 1));
	items_.push_back(new Weather(3600, 0, 1));
	items_.push_back(new Volume(3600, 1, 1));
	items_.push_back(new Date(60, 0, 1));

	items_.shrink_to_fit();
}
