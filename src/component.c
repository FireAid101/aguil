#include "component.h"

component create_new_component(component_type type, void *ptr_data)
{
	component result;

	result.(*ptr_callback)() = NULL;
	result.type = type;
	result.ptr_data = ptr_data;
}

text create_text(char *str)
{

}

text create_text_at(char *str, int x, int y)
{

}
