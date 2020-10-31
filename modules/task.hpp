#ifndef __TASK_H__
#define __TASK_H__

#include "../item.hpp"

class Task : public Item
{
public:
    Task(std::string name, int update_interval, bool has_event_handler, bool has_clicked);
    int SetValue();
    void Clicked(int button);
private:
    int GetTaskValue(const char* command);
};


#endif // __NEWS_H__
