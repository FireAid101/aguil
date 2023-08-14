#include "data.h"

void stack_push(void *ptr, stack *st)
{
	if (st->cursor < MAX_STACK)
	{
		st->cursor += 1;
		st->stack[st->cursor] = ptr;
	}

}

void *stack_pop(stack *st)
{
	if (st->cursor > 0)
	{
		void *ptr = st->stack[st->cursor];
		st->cursor -= 1;

		return ptr;
	}
	return NULL;
}
