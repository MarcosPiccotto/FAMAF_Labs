#ifndef __STACK_C__
#define __STACK_C__
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

stack stack_empty()
{
    stack new_stack = malloc(sizeof(stack));
    new_stack->size = 0;
    new_stack->first = NULL;

    return new_stack;
}

stack stack_push(stack s, stack_elem e)
{
    stack_node *new_node = malloc(sizeof(stack_node));
    new_node->elem = e;
    new_node->next = s->first;

    stack new_stack = malloc(sizeof(struct _s_stack));
    new_stack->size = s->size + 1;
    new_stack->first = new_node;

    return new_stack;
}

stack stack_pop(stack s)
{
    assert(!stack_is_empty(s));
    stack_node *temp = s->first;
    s->first = s->first->next;
    free(temp);
    s->size--;
    return s;
}

unsigned int stack_size(stack s)
{
    return s == NULL ? 0 : s->size;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->first->elem;
}

bool stack_is_empty(stack s)
{
    return s == NULL;
}

stack_elem *stack_to_array(stack s)
{
    unsigned int size = stack_size(s);
    if (size == 0)
    {
        return NULL;
    }
    stack_elem *array = malloc(size * sizeof(stack_elem));

    stack_node *current = s->first; // Puntero para recorrer los nodos del stack

    for (unsigned int i = 0; i < size; i++)
    {
        array[i] = current->elem;
        current = current->next;
    }

    return array;
}

stack stack_destroy(stack s)
{
    while (s->first != NULL)
    {
        stack_node *next = s->first->next;
        free(s->first);
        s->first = next;
        s->size--;
    }
    free(s);
    return NULL;
}
#endif