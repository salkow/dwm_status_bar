#ifndef __UPDATES_H__
#define __UPDATES_H__

#include "../item.hpp"

class Updates : public Item
{
public:
    Updates(ItemData* data, int signal);
    int SetValue();
    void Clicked(int button);
};

#endif // __UPDATES_H__
