#ifndef __VOLUME_HPP__
#define __VOLUME_HPP__

#include "../item.hpp"

#include "alsa/asoundlib.h"

#define MAX_CARDS 256
#define DEVICE "default"
#define SELEM_NAME "Master"

class Volume : public Item
{
public:
    Volume(int update_interval, bool has_event_handler, bool needs_internet, 
		   bool has_clicked);
    void UpdateWhenEvent();
    int SetValue();
    void Clicked(int button);

private:
    int MonitorNative(char const *name);
    int OpenCtl(const char *name, snd_ctl_t **ctlp);
    void CloseAll(snd_ctl_t* ctls[], int ncards);
};

#endif // __VOLUME_HPP__
