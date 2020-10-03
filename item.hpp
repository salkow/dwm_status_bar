#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <string>

#include <fcntl.h>
#include <unistd.h>

class Item
{
public:
    virtual int SetValue() = 0;
    virtual void UpdateWhenEvent();

    Item(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    virtual ~Item();

    int update_interval_;
    const int default_update_interval_;
    std::string value_;
    int signal_;
    bool is_active_;
    bool has_event_handler_;
	bool needs_internet_;
};

#endif // __ITEM_HPP__
