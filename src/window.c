#include "window.h"

window create_window(char *title, vec2 position, vec2 size, application *ptr, int font_height)
{
	window result;

	TTF_SetFontSize(ptr->font, font_height);

	// Load font
	SDL_Color text_color = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderUTF8_Blended(ptr->font, title, text_color);
	result.title_texture = SDL_CreateTextureFromSurface(ptr->ren_context, surface);
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

	result.program_ptr = ptr;	

	result.is_focused = false;

	return result;
}

void window_begin_render(window *ptr)
{

	// Create border
	SDL_Rect border;
	border.x = ptr->titlebar.x;
	border.y = ptr->titlebar.y;
	border.w = ptr->titlebar.w;
	border.h = ptr->titlebar.h + ptr->frame.h;

	// Make renderer pointer and push window to the stack
	SDL_Renderer *ren = ptr->program_ptr->ren_context;
	stack_push(ptr,&ptr->program_ptr->window_stack);

	// Draw titlebar and frame
	SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);
	SDL_RenderFillRect(ren, &ptr->titlebar);

	SDL_SetRenderDrawColor(ren, 30, 30, 30, 255);
	SDL_RenderFillRect(ren, &ptr->frame);

	// Render border
	SDL_RenderCopy(ren, ptr->title_texture, NULL, &ptr->text_dst);
	SDL_SetRenderDrawColor(ren, 80, 80, 80, 255);
	SDL_RenderDrawRect(ren, &border);
}

void window_end_render(window *ptr)
{
	void *top = stack_pop(&ptr->program_ptr->window_stack);	
}

