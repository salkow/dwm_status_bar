#ifndef __NEWS_H__
#define __NEWS_H__

#include "../item.hpp"

class News : public Item
{
public:
    News(ItemData* data, int signal);
    int SetValue();
    void Clicked(int button);
};


#endif // __NEWS_H__
