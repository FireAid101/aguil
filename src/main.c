#include <SDL2/SDL.h>
#include <stdbool.h>

#include <stdio.h>
#include "application.h"
#include "window.h"

// Global program -- The first program that is run
static application program;
static window win, win2;

void draw()
{
	window_begin_render(&win);	
	window_end_render(&win);

	window_begin_render(&win2);
	window_end_render(&win2);
}

int main(int argc, char** argv)
{
	if (create_application(&program, "Test", 800, 600) != true)
	{
		printf("Error creating application\n");
		return 1;
	}

	vec2 pos = {100, 100};
	vec2 size = {200, 200};
	win = create_window("Hello", pos, size, &program, 15);

	vec2 pos2 = {530, 100};
	vec2 size2 = {200, 200};
	win2 = create_window("World", pos2, size2, &program, 25);

	program.render = draw;

	run_application(&program);

	if (close_application(&program) != true)
	{
		printf("Error closing the application\n");
		return 1;
	}
	return 0;
}

