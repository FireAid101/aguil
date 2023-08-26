#ifndef COMPONENT_H

#define COMPONENT_H

#include "context.h"
#include "data.h"
#include <stdbool.h>

typedef enum
{
	ct_text,
	ct_button,
} component_type;

typedef struct
{
	component_type type;
	SDL_Rect area;
  SDL_Point own_position;
	void *ptr_data;
	void (*ptr_callback)(); // Really depends on the type of component
} component;

component create_text(char *str, int font_size, int window_width);
component create_text_at(char *str, int x, int y, int font_size, int window_width);

component create_button(char *text, int font_size, int window_width, void *ptr_clicked);

typedef struct
{
	char *data;
	color text_color;
	SDL_Texture *texture;
} text;
void unload_text(text *ptr_text);

typedef struct
{
	char *text;
	color text_color, button_color, button_highlighted_color, button_clicked_color;

	bool is_clicked;
	color current_color;
	SDL_Texture *texture;
} button;

void handle_button_events(component *ptr_button);
void unload_button(button *ptr_button);

#endif
