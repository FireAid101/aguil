#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "data.h"

/*
 *	This is a binding over the SDL2 window and renderer for our GUI library.
 *	We are going to use this application structure for housing and controlling our GUI for an invidual OS-level window
 */
typedef struct 
{
	TTF_Font *font;
	SDL_Window *win_context;
	SDL_Renderer *ren_context;
	SDL_Event *event;

	stack window_stack;
	void *focused_window;

	SDL_Surface *surf;
	SDL_Texture *texture;
	
	void (*render)(); // Function pointers to the code defined by the developer 
} application;

bool create_application(application *ptr_application, const char *window_name, int width, int height);

bool close_application(application *ptr_application);

void run_application(application *ptr_application);

#include "window.h"
#endif
