#include "item.hpp"

static int next_available_signal = 0;

Item::Item(std::string name, int update_interval, bool has_event_handler, bool has_clicked)
	: name_(name), default_update_interval_(update_interval), is_active_(true),
	  has_event_handler_(has_event_handler), has_clicked_(has_clicked)
{
	signal_ = next_available_signal++;
}

Item::~Item(){}

void Item::UpdateWhenEvent(){}

void Item::Clicked(int button){}
