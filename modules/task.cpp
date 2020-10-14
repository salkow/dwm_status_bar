#include "task.hpp"

#include <cstdio>
#include <fmt/core.h>
#include <string>

Task::Task(int update_interval, bool has_event_handler, bool needs_internet,
           bool has_clicked)
    : Item(update_interval, has_event_handler, needs_internet, has_clicked) {}

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
    int due_in_seven_days = GetTaskValue("task +DUE status:pending count 2>/dev/null");
    int due_today = GetTaskValue("task +TODAY status:pending count 2>/dev/null");
    int overdue = GetTaskValue("task +OVERDUE count 2>/dev/null");

    if (due_in_seven_days == -1 || due_today == -1 || overdue == -1)
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
        system("setsid -f st -t vit -e zsh -c 'vit && zsh' >/dev/null 2>&1");
    }
}