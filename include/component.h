#ifndef COMPONENT_H
#define COMPONENT_H

#include "context.h"

typedef SDL_Color color;

typedef enum
{
	ct_text,
} component_type;

typedef struct
{
	component_type type;
	SDL_Rect area;
  SDL_Point own_position;
	void *ptr_data;
	void (*ptr_callback)(); // Really depends on the type of component
} component;

component create_text(char *str, color text_color, int font_size, int window_width);
component create_text_at(char *str, color text_color, int x, int y, int font_size, int window_width);

typedef struct
{
	char *data;
	color text_color;
	SDL_Texture *texture;
} text;
void unload_text(text *ptr_text);

#endif
