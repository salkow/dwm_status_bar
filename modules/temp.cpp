#include <cstdio>
#include <fmt/core.h>
#include <string>

#include "temp.hpp"

int SetTemp(Item* temp)
{
    FILE* fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");

    if (fp == nullptr)
    {
        temp->_is_active = false;
        return;
    }

    std::string old_value = temp->_value; 

    int temp_num = 0;

    fscanf(fp, "%d", &temp_num);

    temp->_value = fmt::format("{}°C", temp_num / 1000);

    return temp->_value != old_value;
}