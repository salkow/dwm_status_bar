#ifndef __VOLUME_HPP__
#define __VOLUME_HPP__

#include "../item.hpp"

class Volume : public Item
{
public:
    Volume(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();
};

#endif // __VOLUME_HPP__
