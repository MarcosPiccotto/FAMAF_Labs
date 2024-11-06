#ifndef __STACK_C__
#define __STACK_C__
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

stack stack_empty()
{
    stack new_stack = malloc(sizeof(_s_stack));
    new_stack = NULL;
    return new_stack;
}

stack stack_push(stack s, stack_elem e)
{
    stack new_elem = malloc(sizeof(_s_stack));
    new_elem->elem = e;
    new_elem->next = s;
    return new_elem;
}

stack stack_pop(stack s)
{
    assert(!stack_is_empty(s));
    stack aux_elem = s;
    s = s->next;
    free(aux_elem);
    return s;
}

unsigned int stack_size(stack l)
{
    unsigned int count = 0;
    stack p = l;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elem;
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

    for (unsigned int i = 0; i < size; i++)
    {
        array[i] = s->elem;
        s = s->next;
    }

    return array;
}

stack stack_destroy(stack s)
{
    while (s != NULL)
    {
        stack next = s->next;
        free(s);
        s = next;
    }

    return NULL;
}
#endif