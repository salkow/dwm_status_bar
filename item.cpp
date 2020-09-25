#include "item.hpp"

Item::Item(int update_interval, int signal, bool has_event_handler, bool needs_internet)
    : default_update_interval_(update_interval), signal_(signal),
      is_active_(true), has_event_handler_(has_event_handler), needs_internet_(needs_internet) {}

Item::~Item(){}

void Item::UpdateWhenEvent(){}
