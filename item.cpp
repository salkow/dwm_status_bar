#include "item.hpp"

static int next_available_signal = 0;

Item::Item(int update_interval, bool has_event_handler, bool needs_internet,
		   bool has_clicked)
	: default_update_interval_(update_interval), is_active_(true),
	  has_event_handler_(has_event_handler), needs_internet_(needs_internet),
	  has_clicked_(has_clicked)
{
	signal_ = next_available_signal++;
}

Item::~Item(){}

void Item::UpdateWhenEvent(){}

void Item::Clicked(int button){}
