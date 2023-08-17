#include "component.h"

component create_new_component(component_type type, void *ptr_data)
{
	component result;

	result.type = type;
	result.ptr_data = ptr_data;
	result.ptr_callback = NULL;

	return result;
}

text create_text(char *str, color text_color)
{
	text result;

	result.data = str;
	result.text_color = text_color;
	
	SDL_Surface *surf = TTF_RenderUTF8_Blended(global_context->font_context, str, result.text_color);
	result.texture = SDL_CreateTextureFromSurface(global_context->ren_context, surf);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(result.texture, NULL, NULL, &w, &h);

	result.own_position.x = 0;
	result.own_position.y = 0;

	result.area.x = -1;
	result.area.y = -1;
	result.area.w = w;
	result.area.h = h;

	return result;
}

text create_text_at(char *str, color text_color, int x, int y)
{
	text result;

	result.data = str;
	result.text_color = text_color;
	
	SDL_Surface *surf = TTF_RenderUTF8_Blended(global_context->font_context, str, result.text_color);
	result.texture = SDL_CreateTextureFromSurface(global_context->ren_context, surf);
	SDL_FreeSurface(surf);

	int w, h;
	SDL_QueryTexture(result.texture, NULL, NULL, &w, &h);

	result.own_position.x = x;
	result.own_position.y = y;

	result.area.x = x;
	result.area.y = y;
	result.area.w = w;
	result.area.h = h;

	return result;
}

void unload_text(text *ptr_text)
{
	SDL_DestroyTexture(ptr_text->texture);
}
