#ifndef __STATUS_BAR_HPP__
#define __STATUS_BAR_HPP__

#include <string>

#include "item.hpp"

class StatusBar
{
public:
	StatusBar();

	void Start();

	void SetValue();

	void SetRoot();
private:
	std::string _status_bar_str;

	Item* _items;
	int _num_of_items;
};

#endif // __STATUS_BAR_HPP__
