#ifndef __TEMP_H__
#define __TEMP_H__

#include "../item.hpp"

class Temp : public Item
{
public:
    Temp(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();
};

#endif // __TEMP_H__
