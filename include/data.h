#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int x, y;
} vec2; // A simple data structure for storing 2d points and values

#define MAX_STACK 20

typedef struct
{
	int cursor;
	void *stack[MAX_STACK];
} stack;

void stack_push(void *ptr, stack *st);
void *stack_pop(stack *st);

#endif
