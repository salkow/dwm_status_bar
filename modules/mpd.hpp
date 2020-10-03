#ifndef __MPD_H__
#define __MPD_H__

#include "../item.hpp"

#include <mpd/client.h>

class Mpd : public Item
{
public:
    Mpd(int update_interval, int signal, bool has_event_handler, bool needs_internet);
    int SetValue();
    void UpdateWhenEvent();

private:
	struct mpd_connection* con_;

};

#endif // __MPD_H__