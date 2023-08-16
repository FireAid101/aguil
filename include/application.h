#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdbool.h>
#include <stdlib.h>
#include "data.h"

#include "context.h"
#include "window.h"
/*
 *	This is a binding over the SDL2 window and renderer for our GUI library.
 *	We are going to use this application structure for housing and controlling our GUI for an invidual OS-level window
 */

typedef struct 
{
	int window_count;
	window *ptr_windows;
	
} application;

bool create_application(application *ptr_application, const char *window_name, int width, int height);

bool close_application(application *ptr_application);

void add_window(application *ptr, window *ptr_new_window);

void run_application(application *ptr_application);

#endif
