#ifndef __TEMP_H__
#define __TEMP_H__

#include "../item.hpp"

class Temp : public Item
{
public:
    Temp(ItemData* data, int signal);
    int SetValue();
};

#endif // __TEMP_H__
