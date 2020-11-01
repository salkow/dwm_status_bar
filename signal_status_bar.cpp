#include "config.hpp"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "You must specify only name of the module.\n";
        return 1;
    }

    int num_of_items = sizeof(item_data) / sizeof(ItemData);

    char status_bar_signal[4];

    for (int i = 0; i < num_of_items; i++)
    {
        if (!strcmp((item_data[i].name_).c_str(), argv[1]))
        {
            snprintf(status_bar_signal, 4, "%03d", i);

            int fd = open(FIFO_FILE, O_WRONLY | O_NONBLOCK);
            write(fd, status_bar_signal, 3);
            close(fd);

            return 0;
        }
    }

    std::cout << "Couldn't find the name.\n";

    return 2;
}
