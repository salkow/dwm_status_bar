#ifndef __TASK_H__
#define __TASK_H__

#include "../item.hpp"

class Task : public Item
{
public:
    Task(ItemData* data, int signal);
    int SetValue();
    void Clicked(int button);
private:
    int GetTaskValue(const char* command);
};

#endif // __NEWS_H__
