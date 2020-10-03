#include "mpd.hpp"

#include <fmt/core.h>
#include <string>

Mpd::Mpd(int update_interval, int signal, bool has_event_handler, bool needs_internet)
    : Item(update_interval, signal, has_event_handler, needs_internet) {}

int Mpd::SetValue()
{
	struct mpd_connection* con;
	struct mpd_status *status;
	struct mpd_song *song;
	int status_type;
	const char *artist = NULL, *title = NULL;

	con = mpd_connection_new(NULL, 0, 30000);
	if(mpd_connection_get_error(con)) 
	{
		mpd_connection_free(con);
        //error
	}

	mpd_command_list_begin(con, true);
	mpd_send_status(con);
	mpd_send_current_song(con);
	mpd_command_list_end(con);

	status = mpd_recv_status(con);
	if(!status) 
	{
		mpd_connection_free(con);

        is_active_ = false;
        return 1;
	}

	mpd_response_next(con);

	song = mpd_recv_song(con);

	title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
	if(!title)
	{
		title = mpd_song_get_uri(song);
	}

	artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);

    std::string old_value = value_;

	status_type = mpd_status_get_state(status);
	switch(status_type) 
    {
		case(MPD_STATE_PLAY):
            value_ = fmt::format("▶️ {} - {}", artist, title);
			break;
		case(MPD_STATE_PAUSE):
            value_ = fmt::format("⏸️ {} - {}", artist, title);
			break;
		case(MPD_STATE_STOP):
			value_ = "";
            is_active_ = false;
            return 1;
		default:
            is_active_ = false;
            return 1;
	}

	mpd_song_free(song);
	mpd_response_finish(con);
	mpd_status_free(status);
	mpd_connection_free(con);

    is_active_ = true;

    return value_ != old_value;
}

void Mpd::UpdateWhenEvent()
{
	struct mpd_connection* con = mpd_connection_new(NULL, 0, 30000);

    while(true)    
    {
	    mpd_run_idle_mask(con, MPD_IDLE_PLAYER);

		// Signal application to update the volume.
		int fd = open("/home/salkow/Projects/dwm_status_bar/update_fifo", O_WRONLY | O_NONBLOCK);
	    write(fd, "08", 2);
	    close(fd);
    }

    mpd_connection_free(con);

    is_active_ = 0;
}