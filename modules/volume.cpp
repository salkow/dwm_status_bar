#include "volume.hpp"
#include "../config.hpp"

#include "fmt/core.h"
#include "string"

Volume::Volume(ItemData* data, int signal)
    : Item(data, signal) {}

int Volume::SetValue()
{
	const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;

	long vol;
	snd_mixer_t *h_mixer;
	snd_mixer_selem_id_t *sid;
	snd_mixer_elem_t *elem ;

	if (snd_mixer_open(&h_mixer, 1) < 0)
    {
		is_active_ = false;
        return 1;
    }

	if (snd_mixer_attach(h_mixer, DEVICE) < 0)
    {
		is_active_ = false;
        return 1;
    }

	if (snd_mixer_selem_register(h_mixer, NULL, NULL) < 0)
    {
		is_active_ = false;
        return 1;
    }

	if (snd_mixer_load(h_mixer) < 0)
    {
		is_active_ = false;
        return 1;
    }

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, SELEM_NAME);

	if ((elem = snd_mixer_find_selem(h_mixer, sid)) == NULL)
    {
		is_active_ = false;
		return 1;
    }

    long minvolume, maxvolume;

    snd_mixer_selem_get_playback_volume_range (elem, &minvolume, &maxvolume);

	snd_mixer_selem_get_playback_volume(elem, CHANNEL, &vol);

    int not_muted;

	snd_mixer_selem_get_playback_switch(elem, CHANNEL, &not_muted);

	snd_mixer_close(h_mixer);

    // Convert from dB to percentage.
	vol -= minvolume;
	maxvolume -= minvolume;

    // Round number.
	float float_vol = (float) 100 * vol / maxvolume;
    vol = (float_vol < 0 ? (float_vol - 0.5) : (float_vol + 0.5));

    std::string old_value = value_;

    if (not_muted == 0)
    {
        value_ = "🔇";
    }

    else
    {
        std::string vol_icon;

        if (vol < 33)
        {
            vol_icon = "🔈";
        } 

        else if (vol < 66)
        {
            vol_icon = "🔉";
        }

        else
        {
            vol_icon = "🔊";
        }

        value_ = fmt::format("{} {}%", vol_icon, vol);
        value_ = fmt::format("{} {}%", vol_icon, vol);
    }

    return value_ != old_value;
}

void Volume::UpdateWhenEvent()
{
    char status_bar_signal[4];
    snprintf(status_bar_signal, 4, "%03d", signal_);

    while(MonitorNative(DEVICE) == 0)
	{
		// Signal application to update the volume.
		int fd = open(FIFO_FILE, O_WRONLY | O_NONBLOCK);
        write(fd, status_bar_signal, 4);
        close(fd);
    }

    is_active_ = 0;
}

int Volume::MonitorNative(char const *name) 
{
    snd_ctl_t *ctls[MAX_CARDS];
    int ncards = 0;
    int i, err = 0;

    if (!name) 
	{
        int card = -1;

        while (snd_card_next(&card) >= 0 && card >= 0) 
		{
            char cardname[16];
            if (ncards >= MAX_CARDS) 
			{
                CloseAll(ctls, ncards);
                return 1;
            }

            sprintf(cardname, "hw:%d", card);
            err = OpenCtl(cardname, &ctls[ncards]);

            if (err < 0) 
			{
                CloseAll(ctls, ncards);
                return err;
            }

            ncards++;
        }
    } 

	else 
	{
        err = OpenCtl(name, &ctls[0]);
        if (err < 0) 
		{
            CloseAll(ctls, ncards);
            return err;
        }

        ncards++;
    }

	while (ncards > 0)
	{
        pollfd* fds = new pollfd[ncards];

        for (i = 0; i < ncards; i++) 
		{
            snd_ctl_poll_descriptors(ctls[i], &fds[i], 1);
        }

        err = poll(fds, ncards, -1);
        if (err <= 0) {
            err = 0;
            break;
        }

        for (i = 0; i < ncards; i++) 
		{
            unsigned short revents;
            snd_ctl_poll_descriptors_revents(ctls[i], &fds[i], 1, &revents);
            if (revents & POLLIN) 
			{
                snd_ctl_event_t *event;
                snd_ctl_event_alloca(&event);

                if (snd_ctl_read(ctls[i], event) < 0) 
				{
                    continue;
                }

                if (snd_ctl_event_get_type(event) != SND_CTL_EVENT_ELEM) 
				{
                    continue;
                }

                unsigned int mask = snd_ctl_event_elem_get_mask(event);
                if (mask & SND_CTL_EVENT_MASK_VALUE) {
                    CloseAll(ctls, ncards);
                    return 0;
                }
            }
        }
    }

    CloseAll(ctls, ncards);
    return 1;
}

int Volume::OpenCtl(const char *name, snd_ctl_t **ctlp) 
{
    snd_ctl_t *ctl;

    int err = snd_ctl_open(&ctl, name, SND_CTL_READONLY);
    if (err < 0) 
	{
        // fprintf(stderr, "Cannot open ctl %s\n", name);
        return err;
    }

    err = snd_ctl_subscribe_events(ctl, 1);
    if (err < 0) 
	{
        // fprintf(stderr, "Cannot open subscribe events to ctl %s\n", name);
        snd_ctl_close(ctl);
        return err;
    }

    *ctlp = ctl;
    return 0;
}

void Volume::CloseAll(snd_ctl_t* ctls[], int ncards) 
{
    for (ncards -= 1; ncards >= 0; --ncards) 
	{
        snd_ctl_close(ctls[ncards]);
    }
}

void Volume::Clicked(int button)
{
    if (button == 1)
    {
		system(fmt::format("setsid -f {0} -t alsamixer -e {1} -c 'alsamixer && {1}'", TERMINAL, SHELL).c_str());
    }

    else if (button == 2)
    {
        system("setsid -f amixer set Master toggle");
    }

    else if (button == 4)
    {
        system("setsid -f amixer set Master 5%+");
    }

    else if (button == 5)
    {
        system("setsid -f amixer set Master 5%-");
    }
}
