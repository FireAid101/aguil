#include <stdio.h>
#include "context.h"
#include "application.h"

int main(int argc, char** argv)
{
	application program;
	window win, win2;

	if (create_application(&program, "Test", 800, 600) != true)
	{
		printf("Error creating application\n");
		return 1;
	}

	// Create windows
	vec2 pos = {100, 100};
	vec2 size = {200, 200};
	win = create_window("Hello", pos, size, 15);

	vec2 pos2 = {530, 100};
	vec2 size2 = {200, 200};
	win2 = create_window("World", pos2, size2, 25);

	// Add windows to the program
	add_window(&program, &win);
	add_window(&program, &win2);

	// Run
	run_application(&program);

	if (close_application(&program) != true)
	{
		printf("Error closing the application\n");
		return 1;
	}
	return 0;
}
