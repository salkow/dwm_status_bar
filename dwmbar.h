#ifndef __DWMBAR_H__
#define __DWMBAR_H__

struct _item;
typedef struct _item item;

typedef void (*Func)(item*);

typedef struct _item
{
	char icon[8];
	char value[50];
	int update_period;
	int signal;
	int is_active;
	Func SetValue;
}item;

void SetStatusBar(item* status_bar_items, int num_of_items, char* status_bar);

void SetRoot(char* status_bar_str);

#endif // __DWMBAR_H__
