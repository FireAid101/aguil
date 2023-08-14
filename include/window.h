#ifndef WINDOW_H
#define WINDOW_H

#include "data.h"
#include "application.h"

typedef struct
{
	SDL_Rect frame, titlebar;
	char *title;
	application *program_ptr;
	SDL_Texture *title_texture;
	SDL_Rect text_dst;
	bool is_focused;
} window;

window create_window(char *title, vec2 position, vec2 size, application *ptr, int font_height);
void window_begin_render(window *ptr); // For immediate mode
void window_end_render(window *ptr); // For immediate mode
#endif
