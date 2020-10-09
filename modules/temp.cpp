#include "temp.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

Temp::Temp(int update_interval, bool has_event_handler, bool needs_internet, 
		   bool has_clicked)
    : Item(update_interval, has_event_handler, needs_internet, has_clicked) {}

int Temp::SetValue()
{
    FILE* fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");

    if (fp == nullptr)
    {
        is_active_ = false;
        return 1;
    }

    std::string old_value = value_; 

    int temp_num = 0;

    fscanf(fp, "%d", &temp_num);

    fclose(fp);

    value_ = fmt::format("🌡{}°C", temp_num / 1000);

    return value_ != old_value;
}
