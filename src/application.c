#include "application.h"

bool create_application(application *ptr_application, const char *window_name, int width, int height, context *ptr_context)
{
	// Start SDL2 and init the contexts
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	ptr_application->ptr_context = ptr_context;
	ptr_application->ptr_context->win_context = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	ptr_application->ptr_context->ren_context = SDL_CreateRenderer(ptr_application->ptr_context->win_context, -1 , 0);

	ptr_application->ptr_context->font_context = TTF_OpenFont("Roboto-Regular.ttf", 15);

	// Check to see if the contexts are working correctly
	if (ptr_application->ptr_context->win_context == NULL || ptr_application->ptr_context->ren_context == NULL)
	{
		printf("AGUIL Error: Failed to create window %s.", window_name);
		return false;
	}

	ptr_application->ptr_context->event_context = malloc(sizeof(SDL_Event));

	ptr_application->window_count = 0;
	ptr_application->ptr_windows = NULL; 

	return true;
}

bool close_application(application *ptr_application)
{
	free(ptr_application->ptr_context->event_context);
	free(ptr_application->ptr_windows);
	SDL_DestroyRenderer(ptr_application->ptr_context->ren_context);
	SDL_DestroyWindow(ptr_application->ptr_context->win_context);
	TTF_CloseFont(ptr_application->ptr_context->font_context);
	TTF_Quit();
	SDL_Quit();
	return true;
}

void run_application(application *ptr_application)
{
	bool isDone = false;

	while (!isDone)
	{
		// Handle events
		while (SDL_PollEvent(ptr_application->ptr_context->event_context))
		{
			switch (ptr_application->ptr_context->event_context->type)
			{
				case SDL_QUIT:
					isDone = true;
					break;
			}

		}

		SDL_SetRenderDrawColor(ptr_application->ptr_context->ren_context, 0, 0, 0, 255);
		SDL_RenderClear(ptr_application->ptr_context->ren_context);

		for (int i = 0; i < ptr_application->window_count; i++)
		{
			window win = ptr_application->ptr_windows[i];
			render_window(&win);
		}

		SDL_RenderPresent(ptr_application->ptr_context->ren_context);
	}
}

void add_component(application *ptr, void *component, component_type type)
{
	int index;
	window *new_size;
	window new_window;

	switch (type)
	{
		case t_WINDOW:
			new_window = *(window*)component;
			index = ptr->window_count;

			if (index > 0)
			{
				new_size = realloc(ptr->ptr_windows, sizeof(window) * (index + 1));
			}
			else
			{
				new_size = malloc(sizeof(window));
			}
			ptr->ptr_windows = new_size;
			ptr->ptr_windows[index] = new_window;
			ptr->window_count++;	
			break;
	}
}
