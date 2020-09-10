#include <stdio.h>

#include "temp.h"

int SetTemp(item* temp)
{
    FILE* temp_file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");

    int temp_num = 0;

    fscanf(temp_file, "%d", &temp_num);

    snprintf(temp->value, 15, "%d°C", temp_num / 1000);

    return 1;
}