#include <stdio.h>
#include "application.h"

static context ctx;
int main(int argc, char** argv)
{
	application program;
	window win, win2;

	if (create_application(&program, "Test", 800, 600, &ctx) != true)
	{
		printf("Error creating application\n");
		return 1;
	}

	vec2 pos = {100, 100};
	vec2 size = {200, 200};
	win = create_window("Hello", pos, size, 15, &ctx);

	vec2 pos2 = {530, 100};
	vec2 size2 = {200, 200};
	win2 = create_window("World", pos2, size2, 25, &ctx);

	add_component(&program, &win, t_WINDOW);
	add_component(&program, &win2, t_WINDOW);

	run_application(&program);

	if (close_application(&program) != true)
	{
		printf("Error closing the application\n");
		return 1;
	}
	return 0;
}
