#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "style.h"

typedef struct
{
	SDL_Window *win_context;
	SDL_Renderer *ren_context;
	SDL_Event *event_context;
	TTF_Font *font_context;
	style *style_context;
}context;

extern context *global_context;

#endif
