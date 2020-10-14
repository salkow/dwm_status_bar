#ifndef __TASK_H__
#define __TASK_H__

#include "../item.hpp"

class Task : public Item
{
public:
    Task(int update_interval, bool has_event_handler, bool needs_internet,
         bool has_clicked);
    int SetValue();
    void Clicked(int button);
private:
    int GetTaskValue(const char* command);
};


#endif // __NEWS_H__
