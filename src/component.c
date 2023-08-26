#include "component.h"

component create_text(char *str, int font_size, int window_width)
{
	component result;

	result.ptr_callback = NULL;
	result.type = ct_text;

	text *text_component = malloc(sizeof(text));

	text_component->data = str;
	text_component->text_color = global_context->style_context->text;
	
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

component create_text_at(char *str, int x, int y, int font_size, int window_width)
{
	component result;

	result.type = ct_text;
	result.ptr_callback = NULL;

	text *text_component = malloc(sizeof(text));

	text_component->data = str;
	text_component->text_color = global_context->style_context->text;
	
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

component create_button(char *text, int font_size, int window_width, void *ptr_clicked)
{
	component result;

	result.type = ct_button;
	result.ptr_callback = ptr_clicked;
	
	button *button_component = malloc(sizeof(button));
	
	button_component->is_clicked = false;
	button_component->text = text;
	button_component->text_color = global_context->style_context->text;
	button_component->button_color = global_context->style_context->button;
	button_component->current_color = button_component->button_color;
	button_component->button_highlighted_color = global_context->style_context->button_highlighted;
	button_component->button_clicked_color = global_context->style_context->button_clicked;

	TTF_SetFontSize(global_context->font_context, font_size);
	SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(global_context->font_context, text, button_component->text_color, window_width - 20);
	button_component->texture = SDL_CreateTextureFromSurface(global_context->ren_context, surf);
	SDL_FreeSurface(surf);

	int w,h;
	SDL_QueryTexture(button_component->texture, NULL, NULL, &w, &h);
	
	result.own_position.x = 0;
	result.own_position.y = 0;

	result.area.x = -1;
	result.area.y = -1;
	result.area.w = w + 20;
	result.area.h = h + 6;

	result.ptr_data = button_component;

	return result;
}	

void handle_button_events(component *ptr_component)
{
	SDL_Point mouse_coords;
	button *ptr_button = (button*)ptr_component->ptr_data;
	
	Uint32 button = SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);

	if (button == 0)
	{
			ptr_button->is_clicked = false;
	}

	if (SDL_PointInRect(&mouse_coords, &ptr_component->area) == SDL_TRUE)
	{
		if (button == SDL_BUTTON(1) && ptr_button->is_clicked == false)
		{
			ptr_button->current_color = ptr_button->button_clicked_color;
			ptr_component->ptr_callback();
			ptr_button->is_clicked = true;
		}
		else if (button == SDL_BUTTON(1))
		{	
			ptr_button->current_color = ptr_button->button_clicked_color;
		}
		else
		{
			ptr_button->current_color = ptr_button->button_highlighted_color;
		}
	}		
	else
	{
		ptr_button->current_color = ptr_button->button_color;
	}	
}

void unload_button(button *ptr_button)
{
	SDL_DestroyTexture(ptr_button->texture);
	free(ptr_button);
}
