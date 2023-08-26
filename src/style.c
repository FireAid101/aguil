#include "style.h"
#include "context.h"
#include "application.h"

void set_style_to_dark()
{
	global_context->style_context = malloc(sizeof(style));
	
	style *ptr_style = global_context->style_context;

	ptr_style->window_frame.r = 30;
	ptr_style->window_frame.g = 30;
	ptr_style->window_frame.b = 30;

	ptr_style->window_titlebar.r = 60;
	ptr_style->window_titlebar.g = 60;
	ptr_style->window_titlebar.b = 60;
	
	ptr_style->window_border.r = 80;
	ptr_style->window_border.g = 80;
	ptr_style->window_border.b = 80;

	ptr_style->text.r = 255;
	ptr_style->text.g = 255;
	ptr_style->text.b = 255;

	ptr_style->button.r = 125; 
	ptr_style->button.g = 125; 
	ptr_style->button.b = 125; 

	ptr_style->button_highlighted.r = 100;
	ptr_style->button_highlighted.g = 100;
	ptr_style->button_highlighted.b = 100;
	
	ptr_style->button_clicked.r = 170;
	ptr_style->button_clicked.g = 170;
	ptr_style->button_clicked.b = 170;
}

void set_style_to_light()
{
}

