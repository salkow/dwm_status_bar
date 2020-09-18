#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "modules/date.hpp"
#include "modules/temp.hpp"
#include "modules/updates.hpp"
#include "modules/news.hpp"

// How often we check if the update interval of the items is 0.
#define UPDATE_INTERVAL 10

// Set Update Interval to 0, if you don't want to update it periodically.
const static ConfItem status_bar_items_conf[] =
{
   // Icon, Update Internval(sec), Signal, SetValue Function

//  News
	{  "📰", 		10, 				  1, 	&SetNews    },

//  Updates
	{  "📥", 	    60, 				  2, 	&SetUpdates },

//  Temp
	{  "🌡", 		10, 				   3,    &SetTemp    },

//  DateTime   	
	{  "🗓", 		10,				   	  4, 	 &SetDate    }
};

#endif // __CONFIG_H__
