#ifndef WINDOW_H
#define WINDOW_H

#include "data.h"
#include "context.h"
#include <stdbool.h>
#include "component.h"

typedef struct
{
	SDL_Rect frame, titlebar;
	char *title;
	SDL_Texture *title_texture;
	SDL_Rect text_dst;
	bool visible;

	SDL_Point offset;
	bool grabbed;
} window;

window create_window(char *title, vec2 position, vec2 size, int font_height);
void render_window(window *ptr_window);

void handle_window_movement(window *ptr_window);
void add_component(window *window, component *ptr_component);
#endif
