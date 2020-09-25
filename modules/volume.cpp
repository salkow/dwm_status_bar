#include "volume.hpp"

#include "alsa/asoundlib.h"
#include "fmt/core.h"
#include "string"

Volume::Volume(int update_interval, int signal, bool has_event_handler, bool needs_internet)
    : Item(update_interval, signal, has_event_handler, needs_internet) {}

int Volume::SetValue()
{
	const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;

	long vol;
	snd_mixer_t *h_mixer;
	snd_mixer_selem_id_t *sid;
	snd_mixer_elem_t *elem ;

	char device[] = "default";
	char selem_name[] = "Master";

	if (snd_mixer_open(&h_mixer, 1) < 0)
    {
		is_active_ = false;
        return 0;
    }

	if (snd_mixer_attach(h_mixer, device) < 0)
    {
		is_active_ = false;
        return 0;
    }

	if (snd_mixer_selem_register(h_mixer, NULL, NULL) < 0)
    {
		is_active_ = false;
        return 0;
    }

	if (snd_mixer_load(h_mixer) < 0)
    {
		is_active_ = false;
        return 0;
    }

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);

	if ((elem = snd_mixer_find_selem(h_mixer, sid)) == NULL)
    {
		is_active_ = false;
		return 0;
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
    }

    return value_ != old_value;
}
