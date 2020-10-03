#include "modules/mpd.hpp"
#include "modules/news.hpp"
#include "modules/updates.hpp"
#include "modules/temp.hpp"
#include "modules/keyboard_language.hpp"
#include "modules/weather.hpp"
#include "modules/volume.hpp"
#include "modules/date.hpp"

#include "status_bar.hpp"

void StatusBar::CreateItems()
{
    update_interval_ = 10;
	delim_character_ = '|';

// Update interval, signal, has event handler, needs internet

	items_.push_back(new Mpd			 (3600, 8, 1, 0));
	items_.push_back(new News			 (3600, 1, 0, 0));
	// items_.push_back(new Updates		 (10, 	2, 0, 0));
	items_.push_back(new Temp			 (60, 	3, 0, 0));
	items_.push_back(new KeyboardLanguage(3600, 4, 1, 0));
	items_.push_back(new Weather		 (3600, 5, 0, 0));
	items_.push_back(new Volume			 (3600, 6, 1, 0));
	items_.push_back(new Date			 (60, 	7, 0, 0));

	items_.shrink_to_fit();
}