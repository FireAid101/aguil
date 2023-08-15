#include "window.h"

window create_window(char *title, vec2 position, vec2 size, int font_height, context *ptr_context)
{
	window result;

	result.visible = true;
	result.ptr_context = ptr_context;

	TTF_SetFontSize(ptr_context->font_context, font_height);

	// Load font
	SDL_Color text_color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderUTF8_Blended(ptr_context->font_context, title, text_color);
	result.title_texture = SDL_CreateTextureFromSurface(ptr_context->ren_context, surface);
	SDL_FreeSurface(surface);

	int w,h;

	SDL_QueryTexture(result.title_texture, NULL, NULL, &w, &h);
	
	result.text_dst.x = position.x + 3;
	result.text_dst.y = position.y + 3;
	result.text_dst.w = w;
	result.text_dst.h = h;

	// Create frame and titlebar
	result.title = title; // Not sure if this will work
	
	result.titlebar.x = position.x;
	result.titlebar.y = position.y;
	result.titlebar.w = size.x;
	result.titlebar.h = h + 6;

	result.frame.x = position.x;
	result.frame.y = result.titlebar.y + result.titlebar.h;
	result.frame.w = size.x;
	result.frame.h = size.y;

	return result;
}

void render_window(window *ptr_window)
{

	// Create border
	SDL_Rect border;
	border.x = ptr_window->titlebar.x;
	border.y = ptr_window->titlebar.y;
	border.w = ptr_window->titlebar.w;
	border.h = ptr_window->titlebar.h + ptr_window->frame.h;

	// Make renderer pointer and push window to the stack
	SDL_Renderer *ren = ptr_window->ptr_context->ren_context;

	// Draw titlebar and frame
	SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);
	SDL_RenderFillRect(ren, &ptr_window->titlebar);

	SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);
	SDL_RenderFillRect(ren, &ptr_window->frame);

	SDL_RenderCopy(ren, ptr_window->title_texture, NULL, &ptr_window->text_dst);
	
	// Render border
	//SDL_SetRenderDrawColor(ren, 80, 80, 80, 255);
	//SDL_RenderDrawRect(ren, &border);
}

void handle_window_movement(window *ptr_window)
{
	int mouse_x, mouse_y;
	SDL_Point mouse_point;

	switch(ptr_window->ptr_context->event_context->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouse_x, &mouse_y);
			mouse_point.x = mouse_x;
			mouse_point.y = mouse_y;
			
			if (SDL_PointInRect(&mouse_point, &ptr_window->titlebar) == SDL_TRUE)
			{
				ptr_window->grabbed = true;
				ptr_window->offset.x = ptr_window->titlebar.x - mouse_point.x;
				ptr_window->offset.y = ptr_window->titlebar.y - mouse_point.y;
			}
			
			break;

		case SDL_MOUSEBUTTONUP:
			ptr_window->grabbed = false;
			break;

		case SDL_MOUSEMOTION:
			if (ptr_window->grabbed == true)
			{
				SDL_GetMouseState(&mouse_x, &mouse_y);
				mouse_point.x = mouse_x;
				mouse_point.y = mouse_y;
				ptr_window->titlebar.x = mouse_point.x + ptr_window->offset.x;
			       	ptr_window->titlebar.y = mouse_point.y + ptr_window->offset.y;	
				ptr_window->frame.x = ptr_window->titlebar.x;
				ptr_window->frame.y = ptr_window->titlebar.y + ptr_window->titlebar.h;

				ptr_window->text_dst.x = ptr_window->titlebar.x + 3;
				ptr_window->text_dst.y = ptr_window->titlebar.y + 3;
			}
			break;
	}
}
