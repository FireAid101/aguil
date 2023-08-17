#include "application.h"
#include "context.h"

context *global_context;

bool create_application(application *ptr_application, const char *window_name, int width, int height)
{
	context *ptr_context = malloc(sizeof(context));
	global_context = ptr_context;		

	// Start SDL2 and init the contexts
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	ptr_context->win_context = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	ptr_context->ren_context = SDL_CreateRenderer(ptr_context->win_context, -1 , 0);

	ptr_context->font_context = TTF_OpenFont("Roboto-Regular.ttf", 15);

	// Check to see if the contexts are working correctly
	if (ptr_context->win_context == NULL || ptr_context->ren_context == NULL)
	{
		printf("AGUIL Error: Failed to create window %s.", window_name);
		return false;
	}

	ptr_context->event_context = malloc(sizeof(SDL_Event));

	ptr_application->window_count = 0;
	ptr_application->ptr_windows = NULL; 

	return true;
}

bool close_application(application *ptr_application)
{
	if (ptr_application->window_count > 0)
	{
		for (int i = 0; i < ptr_application->window_count; i++)
		{
			free_components(&ptr_application->ptr_windows[i]);
			free(ptr_application->ptr_windows[i].components);
			SDL_DestroyTexture(ptr_application->ptr_windows[i].title_texture);
		}
	}
	free(global_context->event_context);
	free(ptr_application->ptr_windows);
	SDL_DestroyRenderer(global_context->ren_context);
	SDL_DestroyWindow(global_context->win_context);
	TTF_CloseFont(global_context->font_context);
	TTF_Quit();
	SDL_Quit();
	free(global_context);
	return true;
}

void run_application(application *ptr_application)
{
	bool isDone = false;

	while (!isDone)
	{
		// Handle events
		while (SDL_PollEvent(global_context->event_context))
		{
			switch (global_context->event_context->type)
			{
				case SDL_QUIT:
					isDone = true;
					break;
			}

			for (int i = 0; i < ptr_application->window_count; i++)
			{
				window *win_ptr = &ptr_application->ptr_windows[i];
				handle_window_movement(win_ptr);
			}
		}

		SDL_SetRenderDrawColor(global_context->ren_context, 0, 0, 0, 255);
		SDL_RenderClear(global_context->ren_context);

		for (int i = 0; i < ptr_application->window_count; i++)
		{
			window win = ptr_application->ptr_windows[i];
			render_window(&win);
		}

		SDL_RenderPresent(global_context->ren_context);
	}
}

void add_window(application *ptr, window *ptr_new_window)
{
	int index;
	window *new_size;
	window new_window;

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
	ptr->ptr_windows[index] = *ptr_new_window;
	ptr->window_count++;	
}
