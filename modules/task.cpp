#include "task.hpp"
#include "../config.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

Task::Task(ItemData* data, int signal)
    : Item(data, signal) {}

int Task::GetTaskValue(const char *command)
{
    FILE* fp = popen(command, "r");
    if (fp == nullptr)
    {
        return -1;
    }

    int value = -1;

    fscanf(fp, "%d", &value);

    pclose(fp);

    return value;
}

int Task::SetValue()
{
    int due_in_seven_days = GetTaskValue("task +DUE status:pending count");
    int due_today = GetTaskValue("task +TODAY status:pending count");
    int overdue = GetTaskValue("task +OVERDUE count");

    if (due_in_seven_days == -1 || due_today == -1 || overdue == -1 ||
       (due_in_seven_days == 0  && due_today == 0  && overdue == 0))
    {
        is_active_ = false;
        return 1;
    }

    // We hide value if zero.
    std::string due_in_seven_days_str = (due_in_seven_days > 0) ?
                                        (fmt::format("❕{} ", due_in_seven_days)) :
                                        ("");

    std::string due_today_str = (due_today > 0) ?
                                        (fmt::format("❗{} ", due_today)) :
                                        ("");

    std::string overdue_str = (overdue > 0) ?
                                        (fmt::format("💀{} ", overdue)) :
                                        ("");

    std::string old_value = value_;

    value_ = fmt::format("{}{}{}", due_in_seven_days_str, due_today_str, overdue_str);
    
    // We need to remove last character because don't need it.
    if (!value_.empty())
    {
        value_.pop_back();
    }

    return value_ != old_value;
}

void Task::Clicked(int button)
{
    if (button == 1)
    {
		system(fmt::format("setsid -f {0} -t vit -e {1} -c 'vit && {1}'", TERMINAL, SHELL).c_str());
    }
}
