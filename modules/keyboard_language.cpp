#include "keyboard_language.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <cstdio>
#include <fmt/core.h>
#include <fcntl.h>
#include <unistd.h>

KeyboardLanguage::KeyboardLanguage(int update_interval, int signal, bool has_event_handler, 
								   bool needs_internet, bool has_clicked)
	: Item(update_interval, signal, has_event_handler, needs_internet, has_clicked), 
	  display_(0), device_id_(XkbUseCoreKbd), kbd_desc_ptr_(0) {}

KeyboardLanguage::~KeyboardLanguage()
{
	if(kbd_desc_ptr_ != nullptr)
	{
		XkbFreeKeyboard(kbd_desc_ptr_, 0, True);
	}

	if (display_ != nullptr) 
	{
		XCloseDisplay(display_);
	}
}

void KeyboardLanguage::OpenDisplay(Display** dis)
{
	XkbIgnoreExtension(False);

	char* displayName = strdup(""); // allocates memory for string!
	int eventCode;
	int errorReturn;
	int major = XkbMajorVersion;
	int minor = XkbMinorVersion;
	int reason_return;

	*dis = XkbOpenDisplay(displayName, &eventCode, &errorReturn, &major, &minor, &reason_return);
	free(displayName);

	kbd_desc_ptr_ = XkbAllocKeyboard();

	kbd_desc_ptr_->dpy = *dis;

	if (device_id_ != XkbUseCoreKbd) 
	{
		kbd_desc_ptr_->device_spec = device_id_;
	}
}

int KeyboardLanguage::SetValue()
{
	OpenDisplay(&display_);

	StringVector syms;

	BuildLayout(syms);

	value_ = fmt::format("🌐 {}", syms.at(GetGroup()));

	XCloseDisplay(display_);	

	return 1;
}

void KeyboardLanguage::UpdateWhenEvent()
{
	Display* dis = 0;

	OpenDisplay(&dis);
	
	char status_bar_signal[4];
	snprintf(status_bar_signal, 4, "%03d", signal_);

	while (true)
	{
		WaitEvent(dis);

		// Signal application to update the keyboard language.
		int fd = open("/home/salkow/Projects/dwm_status_bar/update_fifo", O_WRONLY | O_NONBLOCK);

		write(fd, status_bar_signal, 3);
		close(fd);
	}

	XCloseDisplay(dis);
}

LayoutVariantStrings KeyboardLanguage::GetLayoutVariant()
{
	XkbRFVarDefsRecWrapper vdr;
	char* tmp = nullptr;

	XkbRF_GetNamesProp(display_, &tmp, &vdr._it);
	free(tmp);  // return memory allocated by XkbRF_GetNamesProp

	return make_pair(std::string(vdr._it.layout ? vdr._it.layout : "us"),
	                 std::string(vdr._it.variant ? vdr._it.variant : ""));
}

void KeyboardLanguage::BuildLayoutFrom(StringVector& out, const LayoutVariantStrings& lv)
{
	std::istringstream layout(lv.first);
	std::istringstream variant(lv.second);

	while(true) 
	{
		std::string l,v;

		getline(layout, l, ',');
		getline(variant, v, ',');

		if(!layout && !variant) break;

		if(v != "") 
		{
	  		v = "(" + v + ")";
		}

		if(l != "") 
		{
			out.push_back(l+v);
		}
	}
}

void KeyboardLanguage::BuildLayout(StringVector& out)
{
	LayoutVariantStrings lv = this->GetLayoutVariant();
	BuildLayoutFrom(out, lv);
}

void KeyboardLanguage::WaitEvent(Display* dis)
{
	XkbSelectEventDetails(dis, XkbUseCoreKbd,
	XkbStateNotify, XkbAllStateComponentsMask, XkbGroupStateMask);

	XEvent event;

	XNextEvent(dis, &event);
}

int KeyboardLanguage::GetGroup() const
{
	XkbStateRec xkb_state;

	XkbGetState(display_, device_id_, &xkb_state);

	return static_cast<int>(xkb_state.group);
}
