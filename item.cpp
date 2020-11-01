#include "item.hpp"
#include "config.hpp"

Item::Item(ItemData* data, int signal)
	: data_(data), default_update_interval_(data->update_interval_), signal_(signal),
	  is_active_(true) {}

Item::~Item(){}

void Item::UpdateWhenEvent(){}

void Item::Clicked(int button){}
