#include "util.hpp"

#include <sys/file.h>
#include <errno.h>

int IsAlreadyRunning()
{
    int pid_file = open("/tmp/dwm_status_bar.pid", O_CREAT | O_RDWR, 0666);

    int rc = flock(pid_file, LOCK_EX | LOCK_NB);

    if (rc && EWOULDBLOCK == errno)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
