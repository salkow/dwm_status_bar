#ifndef __TEMP_H__
#define __TEMP_H__

#include "../item.hpp"

class Temp : public Item
{
public:
    Temp(std::string name, int update_interval, bool has_event_handler, bool has_clicked);
    int SetValue();
};

#endif // __TEMP_H__
