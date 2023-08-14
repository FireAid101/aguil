/*
 *	This is just the prototype that got me started on creating this library
 * 
 */

//#include <SDL2/SDL.h>
//#include <stdbool.h>


/// Test for a simple GUI library
// I plan to add many features

//int main(int argc, char** argv)
//{
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_Window *window = SDL_CreateWindow("GUI Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 , 0);
/*	SDL_Event event;

	bool isDone = false;

	SDL_Rect panel, titlebar;

	panel.x = 100;
	panel.y = 120;
	panel.w = 200;
	panel.h = 300;

	titlebar.x = 100;
	titlebar.y = 100;
	titlebar.w = 200;
	titlebar.h = 20;

	bool pressed = false;

	SDL_Point offset;
	SDL_Point mousePos;

	while (!isDone)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					isDone = true;
					break;

				case SDL_MOUSEBUTTONDOWN:

					SDL_GetMouseState(&mousePos.x, &mousePos.y);

					if (SDL_PointInRect(&mousePos, &titlebar) == SDL_TRUE)
					{
						pressed = true;

						offset.x = titlebar.x - mousePos.x;
						offset.y = titlebar.y - mousePos.y;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					pressed = false;
					break;

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mousePos.x, &mousePos.y);

					
					if (pressed == true)
					{
						titlebar.x = mousePos.x + offset.x;
					       	titlebar.y = mousePos.y + offset.y;	
						panel.x = titlebar.x;
						panel.y = titlebar.y + titlebar.h;
					}
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
		SDL_RenderFillRect(renderer, &titlebar);

		SDL_SetRenderDrawColor(renderer, 68, 68, 68, 255);
		SDL_RenderFillRect(renderer, &panel);


		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
*/
