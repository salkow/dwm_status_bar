#include "date.hpp"

#include <string.h>
#include <fmt/core.h>
#include <ctime>
#include <string>
#include <iostream>

static char clock_emoji[12][5] = 
	{"🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚"};

Date::Date(int update_interval, bool has_event_handler, bool needs_internet, 
		   bool has_clicked)
	: Item(update_interval, has_event_handler, needs_internet, has_clicked) {}

int Date::SetValue()
{
	std::time_t rawtime = std::time(0);

	std::tm* now = std::localtime(&rawtime);

	char day[4];
	GetDay(now->tm_wday, day);

	char month[4];
	GetMonth(now->tm_mon, month);

	std::string old_value = value_;	

	value_ = fmt::format("🗓 {} {} {} {} | {} {:02}:{:02}",
					day, now->tm_mday, month, now->tm_year + 1900,
					clock_emoji[(now->tm_hour) % 12], now->tm_hour, now->tm_min);

	return value_ != old_value;
}

void Date::GetDay(int id, char* day)
{
	switch (id)
	{
	case 0:
		strcpy(day, "Sun"); break;

	case 1:
		strcpy(day, "Mon"); break;

	case 2:
		strcpy(day, "Tue"); break;

	case 3:
		strcpy(day, "Wed"); break;

	case 4:
		strcpy(day, "Thu"); break;

	case 5:
		strcpy(day, "Fri"); break;

	case 6:
		strcpy(day, "Sat"); break;
	}
}

void Date::GetMonth(int id, char* month)
{
	switch (id)
	{
	case 0:
		strcpy(month, "Jan"); break;

	case 1:
		strcpy(month, "Feb"); break;

	case 2:
		strcpy(month, "Mar"); break;

	case 3:
		strcpy(month, "Apr"); break;

	case 4:
		strcpy(month, "May"); break;

	case 5:
		strcpy(month, "Jun"); break;

	case 6:
		strcpy(month, "Jul"); break;

	case 7:
		strcpy(month, "Aug"); break;

	case 8:
		strcpy(month, "Sep"); break;

	case 9:
		strcpy(month, "Oct"); break;

	case 10:
		strcpy(month, "Nov"); break;

	case 11:
		strcpy(month, "Dec"); break;
	}
}

void Date::Clicked(int button)
{
	if (button == 1)
	{
		system("setsid -f st -t calcurse -e zsh -c 'calcurse && zsh >/dev/null 2>&1'");
	}
}
