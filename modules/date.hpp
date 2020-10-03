#ifndef __DATE_H__
#define __DATE_H__

#include "../item.hpp"

class Date : public Item
{
public:
    Date(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();

private:
    void GetDay(int id, char* day);
    void GetMonth(int id, char* month);
};

#endif // __DATE_H__