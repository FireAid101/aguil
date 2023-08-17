#ifndef WINDOW_H
#define WINDOW_H

#include "data.h"
#include "context.h"
#include <stdbool.h>
#include "component.h"

#define LINE_BREAK_SIZE 10

typedef struct
{
	SDL_Rect frame, titlebar;
	char *title;
	SDL_Texture *title_texture;
	SDL_Rect text_dst;
	bool visible;

	SDL_Point cursor;

	int components_index;
	component *components;

	SDL_Point offset;
	bool grabbed;
} window;

window create_window(char *title, vec2 position, vec2 size, int font_height);
void render_window(window *ptr_window);

void handle_window_movement(window *ptr_window);
void add_component(window *ptr_window, component *ptr_component);

void free_components(window *window);
#endif
