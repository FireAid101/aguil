#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
	SDL_Window *win_context;
	SDL_Renderer *ren_context;
	SDL_Event *event_context;
	TTF_Font *font_context;
}context;

extern context *global_context;

#endif
