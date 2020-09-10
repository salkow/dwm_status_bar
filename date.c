#include <time.h>
#include <stdio.h>
#include <string.h>

#include "date.h"

char clock_emoji[12][5] = 
	{"🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚"};

int SetDate(item* date)
{
	time_t rawtime;	
	time(&rawtime);					

	struct tm* timeinfo = localtime(&rawtime);

	char day[4];
	GetDay(timeinfo->tm_wday, day);

	char month[4];
	GetMonth(timeinfo->tm_mon, month);

	snprintf(date->value, 35, " %s %d %s %d | %s %02d:%02d",
			 day, timeinfo->tm_mday, month, timeinfo->tm_year + 1900,
			 clock_emoji[(timeinfo->tm_hour) % 12], timeinfo->tm_hour, timeinfo->tm_min);

	return 1;
}

void GetDay(int id, char* day)
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

void GetMonth(int id, char* month)
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
