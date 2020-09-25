#ifndef __UPDATES_H__
#define __UPDATES_H__

#include "../item.hpp"

class Updates : public Item
{
public:
    Updates(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();
};

#endif // __UPDATES_H__
