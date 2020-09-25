#ifndef __NEWS_H__
#define __NEWS_H__

#include "../item.hpp"

class News : public Item
{
public:
    News(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();
};


#endif // __NEWS_H__
