#include "window.h"
#include "context.h"

window create_window(char *title, vec2 position, vec2 size, int font_height)
{
	context *ptr_context = global_context;

	window result;
	
	result.components = NULL;
	result.components_index = 0;

	result.grabbed = false;
	result.visible = true;

	TTF_SetFontSize(ptr_context->font_context, font_height);

	// Load font
	SDL_Color text_color = ptr_context->style_context->text;
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
		
	result.cursor.x = result.frame.x + 10;
	result.cursor.y = result.frame.y + 10;

	// create exit button
	result.exit_button = create_button("x", font_height, size.x,{result.visible = false});	

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
	SDL_Renderer *ren = global_context->ren_context;
	
	// Get colors
	color titlebar, frame, border_color;
	titlebar = global_context->style_context->window_titlebar;
	frame = global_context->style_context->window_frame;
	border_color = global_context->style_context->window_border;
	
	if (ptr_window->visible == true)
	{
		// Draw titlebar and frame
		SDL_SetRenderDrawColor(ren, titlebar.r, titlebar.g, titlebar.b, 255);
		SDL_RenderFillRect(ren, &ptr_window->titlebar);

		// Render exit button
		button *exit_button = (button*)ptr_window->exit_button.ptr_data;
		
		ptr_window->exit_button.area.x = (titlebar.x + titlebar.w) - ptr_window_exit_button.area.w - 10;
		ptr_window->exit_button.area.y = titlebar.y + 3;	

		SDL_Rect text_rect = ptr_window->exit_button.area;
		
		SDL_SetRenderDrawColor(ren, exit_button->current_color.r , exit_button->current_color.g, exit_button->current_color.b, 255);
		SDL_RenderFillRect(ren, ptr_window->exit_button.area);		
		
		text_rect.x += 10;
		text_rect.y += 3;
		text_rect.w -= 20;
		text_rect.h -= 6;

		SDL_RenderCopy(ren, button_component->texture, NULL, &text_rect);
		SDL_SetRenderDrawColor(ren, frame.r, frame.g, frame.b, 255);
		SDL_RenderFillRect(ren, &ptr_window->frame);

		SDL_RenderCopy(ren, ptr_window->title_texture, NULL, &ptr_window->text_dst);
	
		// Render border
		SDL_SetRenderDrawColor(ren, border_color.r, border_color.g, border_color.b, 255);
		SDL_RenderDrawRect(ren, &border);
	
		// Render all components
		if (ptr_window->components_index > 0)
		{
			for (int i = 0; i < ptr_window->components_index; i++)
			{
				component *current_component = &ptr_window->components[i];
				text *text_component;
				button *button_component;

				switch (current_component->type)
				{
					case ct_text:
						text_component = (text*)current_component->ptr_data;
						SDL_RenderCopy(ren, text_component->texture, NULL, &current_component->area);
						break;

					case ct_button:
						button_component = (button*)current_component->ptr_data;
					
						SDL_Rect text_rect = current_component->area;
					
						SDL_SetRenderDrawColor(ren, button_component->current_color.r , button_component->current_color.g, button_component->current_color.b, 255);
						SDL_RenderFillRect(ren, &current_component->area);		
		
						text_rect.x += 10;
						text_rect.y += 3;
						text_rect.w -= 20;
						text_rect.h -= 6;

						SDL_RenderCopy(ren, button_component->texture, NULL, &text_rect);
						break;
				}
			}
		}
	}	
}

void handle_window_movement(window *ptr_window)
{
	int mouse_x, mouse_y;
	SDL_Point mouse_point;

	switch(global_context->event_context->type)
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

		// Shifts window and all components inside irrespective of the component type	
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
			
				ptr_window->cursor.x = ptr_window->frame.x + 10;
				ptr_window->cursor.y = ptr_window->frame.y + 10;

				if (ptr_window->components_index > 0)
				{
					for (int i = 0; i < ptr_window->components_index; i++)
					{
						component *current_component = &ptr_window->components[i];
								
						if (current_component->own_position.x > 0)
						{
							current_component->area.x = ptr_window->cursor.x + current_component->own_position.x;
							current_component->area.y = ptr_window->cursor.y + current_component->own_position.y;
						
							ptr_window->cursor.y += current_component->area.h + LINE_BREAK_SIZE;
						}
						else 
						{
							current_component->area.x = ptr_window->cursor.x;
							current_component->area.y = ptr_window->cursor.y;
						
							ptr_window->cursor.y += current_component->area.h + LINE_BREAK_SIZE;	
						}
					}				
				}	
			}
			break;
	}
}

void add_component(window *ptr_window, component *ptr_component)
{
	int index = ptr_window->components_index;
	
// Allocate memory without error
	if (index == 0)
	{
		ptr_window->components = malloc(sizeof(component));
	}
	else
	{
		component *new_size = realloc(ptr_window->components, (index + 1) * sizeof(component));
		ptr_window->components = new_size;
	}

  // If the component has a user-defined position
	if (ptr_component->area.x == -1)
	{
		ptr_component->area.x = ptr_window->cursor.x;
		ptr_component->area.y = ptr_window->cursor.y;

		ptr_window->cursor.y += ptr_component->area.h + LINE_BREAK_SIZE;
	}	
	else
	{
		ptr_component->area.x = ptr_window->cursor.x + ptr_component->area.x;
		ptr_component->area.y = ptr_window->cursor.y + ptr_component->area.y;

		ptr_window->cursor.y += ptr_component->area.h + LINE_BREAK_SIZE;
	}

	ptr_window->components[index] = *ptr_component;
	ptr_window->components_index++;	
}

// Frees based on component type
void free_components(window *window)
{
	if (window->components_index > 0)
	{
		for (int i = 0; i < window->components_index; i++)
		{
			component *current_component = &window->components[i];
			switch (current_component->type)
			{
				case ct_text:
					unload_text((text*)current_component->ptr_data);
					break;

				case ct_button:
					unload_button((button*)current_component->ptr_data);
					break;
			}

		}
	}

}
