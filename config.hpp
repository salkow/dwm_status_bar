#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

class KeyboardLanguage;

#include "modules/mpd.hpp"
#include "modules/news.hpp"
#include "modules/updates.hpp"
#include "modules/temp.hpp"
#include "modules/keyboard_language.hpp"
#include "modules/weather.hpp"
#include "modules/volume.hpp"
#include "modules/date.hpp"
#include "modules/task.hpp"

#include "item.hpp"

#include <string>

template<typename T> 
Item * CreateInstance(std::string name, int update_interval, int has_event_handler, int has_click_event) 
{ return new T(name, update_interval, has_event_handler, has_click_event); }

typedef Item * (*FuncPtr)(std::string name, int update_interval, int has_event_handler, int has_click_event);

typedef struct
{
    std::string name;
    int update_interval;
    int has_event_handler;
    int has_click_event;
    FuncPtr CreateInstancePtr;
} ItemData;

#define UPDATE_INTERVAL 10
#define DELIM_CHARACTER '|'
#define FIFO_FILE "/home/salkow/Projects/dwm_status_bar/update_fifo"
#define SHELL "zsh"
#define TERMINAL "st"

static const ItemData items_data[] =
{
        {"MPD", 3600, 1, 1, CreateInstance<Mpd>},
        {"NEWS", 3600, 0, 1, CreateInstance<News>},
        { "TASK",       1800,   0, 1, CreateInstance<Task>},
        // { "UPDATES",    3600,   0, 0, CreateInstance<Updates>},
        { "TEMP",       60,     0, 0, CreateInstance<Temp>},
        { "LANGUAGE",   3600,   1, 1, CreateInstance<KeyboardLanguage>},
        { "WEATHER",    3600,   0, 1, CreateInstance<Weather>},
        { "VOLUME",     3600,   1, 1, CreateInstance<Volume>},
        { "DATE",       60,     0, 1, CreateInstance<Date>}
};

#endif // __CONFIG_HPP__