#include "application.h"

bool create_application(application *ptr_application, const char *window_name, int width, int height)
{
	// Start SDL2 and init the contexts
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	ptr_application->win_context = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	ptr_application->ren_context = SDL_CreateRenderer(ptr_application->win_context, -1 , 0);

	ptr_application->font = TTF_OpenFont("Roboto-Regular.ttf", 15);
	// Check to see if the contexts are working correctly
	if (ptr_application->win_context == NULL || ptr_application->ren_context == NULL)
	{
		printf("AGUIL Error: Failed to create window %s.", window_name);
		return false;
	}

	ptr_application->event = malloc(sizeof(SDL_Event));

	ptr_application->focused_window = NULL;

	return true;
}

bool close_application(application *ptr_application)
{
	free(ptr_application->event);
	SDL_DestroyRenderer(ptr_application->ren_context);
	SDL_DestroyWindow(ptr_application->win_context);
	TTF_CloseFont(ptr_application->font);
	TTF_Quit();
	SDL_Quit();
	return true;
}

/// NOTE THIS DOES NOT WORK -- THE REASON IS BECAUSE THE STACK HASN'T BEEN ADDED DUE TO IMMEDIATE MODE
/// MUST IMPROVE AND REFACTOR

// Handle window movement
void handle_window_movement(application *ptr)
{
	int mouse_x, mouse_y;
	switch (ptr->event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouse_x, &mouse_y);
			printf("Hello\n");
			for (int i = 0; i < ptr->window_stack.cursor; i++)
			{
				window *win_ptr =(window*)ptr->window_stack.stack[ptr->window_stack.cursor];	
				printf("%s\n", win_ptr->title);
			}
			break;
	}
}


void run_application(application *ptr_application)
{
	bool isDone = false;

	while (!isDone)
	{
		// Handle events
		while (SDL_PollEvent(ptr_application->event))
		{
			switch (ptr_application->event->type)
			{
				case SDL_QUIT:
					isDone = true;
					break;
			}

			handle_window_movement(ptr_application);
		}

		SDL_SetRenderDrawColor(ptr_application->ren_context, 0, 0, 0, 255);
		SDL_RenderClear(ptr_application->ren_context);

		ptr_application->render();

		SDL_RenderPresent(ptr_application->ren_context);
	}
}
