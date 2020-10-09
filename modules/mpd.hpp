#ifndef __MPD_H__
#define __MPD_H__

#include "../item.hpp"

#include <mpd/client.h>

class Mpd : public Item
{
public:
  Mpd(int update_interval, bool has_event_handler, bool needs_internet,
      bool has_clicked);
  int SetValue();
  void UpdateWhenEvent();
  void Clicked(int button);

private:
	struct mpd_connection* con_;

};

#endif // __MPD_H__
