#ifndef COMPONENT_H
#define COMPONENT_H

#include "context.h"

typedef SDL_Color color;

typedef enum
{
	ct_TEXT,
} component_type;

typedef struct
{
	component_type type;
	void *ptr_data;
	void (*ptr_callback)(); // Really depends on the type of component
} component;

component create_new_component(component_type type, void *ptr_data);

typedef struct
{
	char *data;
	color text_color;
	SDL_Rect area;
	SDL_Texture *texture;
	SDL_Point own_position;
} text;

text create_text(char *str, color text_color);
text create_text_at(char *str, color text_color, int x, int y);
void unload_text(text *ptr_text);

#endif
