#ifndef __NEWS_H__
#define __NEWS_H__

#include "../item.hpp"

class News : public Item
{
public:
    News(int update_interval, bool has_event_handler, bool needs_internet,
         bool has_clicked);
    int SetValue();
    void Clicked(int button);
};


#endif // __NEWS_H__
