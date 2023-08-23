#include "component.h"

component create_text(char *str, color text_color, int font_size, int window_width)
{
	component result;

	result.ptr_callback = NULL;
	result.type = ct_text;

	text *text_component = malloc(sizeof(text));

	text_component->data = str;
	text_component->text_color = text_color;
	
	TTF_SetFontSize(global_context->font_context, font_size);
	SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(global_context->font_context, str, text_component->text_color, window_width - 20);
	text_component->texture = SDL_CreateTextureFromSurface(global_context->ren_context, surf);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(text_component->texture, NULL, NULL, &w, &h);

	result.own_position.x = 0;
	result.own_position.y = 0;

	result.area.x = -1;
	result.area.y = -1;
	result.area.w = w;
	result.area.h = h;

	result.ptr_data = text_component;
	return result;
}

component create_text_at(char *str, color text_color, int x, int y, int font_size, int window_width)
{
	component result;

	result.type = ct_text;
	result.ptr_callback = NULL;

	text *text_component = malloc(sizeof(text));

	text_component->data = str;
	text_component->text_color = text_color;
	
	TTF_SetFontSize(global_context->font_context, font_size);
	SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(global_context->font_context, str, text_component->text_color, window_width - x - 20);
	text_component->texture = SDL_CreateTextureFromSurface(global_context->ren_context, surf);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(text_component->texture, NULL, NULL, &w, &h);

	result.own_position.x = x;
	result.own_position.y = y;

	result.area.x = x;
	result.area.y = y;
	result.area.w = w;
	result.area.h = h;

	result.ptr_data = text_component;
	return result;
}

void unload_text(text *ptr_text)
{
	SDL_DestroyTexture(ptr_text->texture);
	free(ptr_text);
}
