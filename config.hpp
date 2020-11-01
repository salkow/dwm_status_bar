#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "modules/mpd.hpp"
#include "modules/news.hpp"
// #include "modules/updates.hpp"
#include "modules/temp.hpp"
#include "modules/keyboard_language.hpp"
#include "modules/weather.hpp"
#include "modules/volume.hpp"
#include "modules/date.hpp"
#include "modules/task.hpp"

#include "item.hpp"

#include <string>

// This is used for assigning a correct CreateInstance function in each module.
template<typename T> 
Item *CreateInstance(ItemData* data, int signal)
{ 
	return new T(data, signal);
}

typedef Item *(*FuncPtr)(ItemData* data, int signal);

struct ItemData
{
    std::string name_;
    int update_interval_;
    bool has_event_handler_;
    bool has_clicked_;
    FuncPtr CreateInstancePtr_;
};

// Options:
#define UPDATE_INTERVAL 10
#define DELIM_CHARACTER '|'
#define FIFO_FILE "/home/salkow/Projects/dwm_status_bar/update_fifo"
#define SHELL "zsh"
#define TERMINAL "st"

static ItemData item_data[] =
{
// 		   Name | UpdateInterval | HasEventHandler | HasClickEvent | CreateInstance Function
        { "MPD", 	 3600, 		      1, 					1,		 CreateInstance<Mpd> },
        { "NEWS", 	 3600, 			  0, 					1, 		 CreateInstance<News> },
        { "TASK",    1800,   		  0, 					1, 		 CreateInstance<Task> },
        // { "UPDATES", 3600,   		  0, 					0, 		 CreateInstance<Updates> },
        { "TEMP",    60,     		  0, 					0, 		 CreateInstance<Temp> },
        { "LANGUAGE",3600,   		  1, 					1, 		 CreateInstance<KeyboardLanguage> },
        { "WEATHER", 3600,   		  0, 					1, 		 CreateInstance<Weather> },
        { "VOLUME",  3600,   		  1, 					1, 		 CreateInstance<Volume> },
        { "DATE",    60,     		  0, 					1, 		 CreateInstance<Date> }
};

#endif // __CONFIG_HPP__
