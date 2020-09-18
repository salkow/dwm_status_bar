#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>

class Item;

typedef int (*Func)(Item*);

// We use a smaller struct in order to make configuration easier.
struct ConfItem
{
    std::string icon;
	int update_interval;
	int signal;
	Func SetValue;
};

struct Item
{
    std::string _icon;

    std::string _value;

	int _update_interval;

    // Singal app to update item.
	int _signal;

	Func _SetValue;

	// Controls if you want to show item with it's current value.
	bool _is_active;

	Item() {}

	Item(std::string icon, int update_interval, int signal, Func SetValue)
	   	: _icon(icon), _update_interval(update_interval), _signal(signal),
		  _SetValue(SetValue), _is_active(true) {}
};

#endif // __ITEM_HPP__