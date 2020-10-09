#ifndef __UPDATES_H__
#define __UPDATES_H__

#include "../item.hpp"

class Updates : public Item
{
public:
    Updates(int update_interval, bool has_event_handler, bool needs_internet,
            bool has_clicked);
    int SetValue();
    void Clicked(int button);
};

#endif // __UPDATES_H__
