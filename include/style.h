#ifndef STYLE_H
#define STYLE_H

#include "data.h"

typedef struct
{
	color window_frame, window_titlebar, window_border;
	color text;
	color button, button_highlighted, button_clicked;
} style;

void set_style_to_dark();
void set_style_to_light();

#endif
