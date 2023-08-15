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

	// Render border
	SDL_RenderCopy(ren, ptr_window->title_texture, NULL, &ptr_window->text_dst);
	SDL_SetRenderDrawColor(ren, 80, 80, 80, 255);
	SDL_RenderDrawRect(ren, &border);
}

