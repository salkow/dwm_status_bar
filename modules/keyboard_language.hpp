#ifndef __KEYBOARD_LANGUAGE_HPP__
#define __KEYBOARD_LANGUAGE_HPP__

#include "../item.hpp"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <map>
#include <cstring>
#include <X11/extensions/XKBrules.h>
#include <string>

typedef std::vector<std::string> StringVector;
typedef std::pair<std::string,std::string> LayoutVariantStrings;

class KeyboardLanguage : public Item
{
public:
	KeyboardLanguage(int update_interval, bool has_event_handler, bool has_clicked);
	~KeyboardLanguage();
	int SetValue();
	void UpdateWhenEvent();
	void Clicked(int button);

private:
	Display* display_;
	int device_id_;
	XkbDescRec* kbd_desc_ptr_;

	// Opens display (or throw std::runtime_error)
	void OpenDisplay(Display** dis);

	// Gets the current layout
	int GetGroup() const;

	// Return layout/variant strings
	LayoutVariantStrings GetLayoutVariant();

	// Returns keyboard layout string
	void BuildLayoutFrom(StringVector& vec, const LayoutVariantStrings& lv);
	void BuildLayout(StringVector& vec);

	// Waits for kb event
	void WaitEvent(Display* dis);
};

// XkbRF_VarDefsRec contains heap-allocated C strings, but doesn't provide a
// direct cleanup method. This wrapper privides a workaround.
// See also https://gitlab.freedesktop.org/xorg/lib/libxkbfile/issues/6
struct XkbRFVarDefsRecWrapper {

	XkbRF_VarDefsRec _it;

	XkbRFVarDefsRecWrapper()
	{
		memset(&_it,0,sizeof(_it));
	}

	~XkbRFVarDefsRecWrapper()
	{
		if(_it.model) std::free(_it.model);
		if(_it.layout) std::free(_it.layout);
		if(_it.variant) std::free(_it.variant);
		if(_it.options) std::free(_it.options);
	}
};


#endif // __KEYBOARD_LANGUAGE_HPP__
