#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "dwmbar.h"
#include "date.h"
#include "temp.h"
#include "updates.h"
#include "news.h"

extern item status_bar_items[] = {

	// Date
	{ "🗓", "", 1, 1, 1, &SetDate },

	// Temp
	{ "🌡", "", 1, 1, 1, &SetTemp },

	// Updates
	{ "📥", "", 1, 1, 1, &SetUpdates },

	// News
	{ "📰", "", 1, 1, 1, &SetNews }
};

#endif // __CONFIG_H__
