#ifndef __DATE_H__
#define __DATE_H__

#include "../item.hpp"

class Date : public Item
{
public:
    Date(ItemData* data, int signal);
    int SetValue();
    void Clicked(int button);

private:
    void GetDay(int id, char* day);
    void GetMonth(int id, char* month);
};

#endif // __DATE_H__
