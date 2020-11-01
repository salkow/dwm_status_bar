#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>

#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

class ItemData;

class Item
{
public:
    virtual int SetValue() = 0;
    virtual void UpdateWhenEvent();
    virtual void Clicked(int button);

    Item(ItemData *data, int signal);
    virtual ~Item();

    ItemData* data_;
    const int default_update_interval_;
    int signal_;
    bool is_active_;

    std::string value_;

};

#endif // __ITEM_HPP__
