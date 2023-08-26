#include <stdio.h>
#include "context.h"
#include "application.h"
#include "style.h"

void clicked()
{
	printf("Clicked\n");
}

int main(int argc, char** argv)
{
	application program;
	window win, win2;

	if (create_application(&program, "Test", 800, 600) != true)
	{
		printf("Error creating application\n");
		return 1;
	}

	set_style_to_dark();
	// Create windows
	vec2 pos = {100, 100};
	vec2 size = {200, 200};
	win = create_window("Hello", pos, size, 15);

	vec2 pos2 = {530, 100};
	vec2 size2 = {200, 200};
	win2 = create_window("World", pos2, size2, 25);

	component new_component = create_text("Hello, world!", 15, win.frame.w); 
	component new_component2 = create_text_at("Hello, world for the second time!", 10, 50, 15, win2.frame.w); 

	component new_component3 = create_button("Click me", 15, win.frame.w, clicked);

	component new_component4 = create_text("hi!", 15, win.frame.w);

	add_component(&win, &new_component);
	add_component(&win2, &new_component2);
	add_component(&win, &new_component3);
	add_component(&win, &new_component4);

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
