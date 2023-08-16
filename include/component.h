#ifndef COMPONENT_H
#define COMPONENT_H

#include "context.h"

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
	
	SDL_Rect area;
	SDL_Texture *texture;
} text;

text create_text(char *str);
text create_text_at(char *str, int x, int y);

#endif
