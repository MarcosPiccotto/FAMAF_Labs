#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>

struct _s_stack
{
    stack_elem *elems;     // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la pila
    unsigned int capacity; // Capacidad actual del arreglo elems
};

stack stack_empty()
{
    stack new_stack = malloc(sizeof(struct _s_stack));
    new_stack->elems = malloc(0);
    new_stack->size = 0;
    new_stack->capacity = 0;
    return new_stack;
}

stack stack_push(stack s, stack_elem e)
{

    if (s->size == s->capacity)
    {
        unsigned int new_capacity = (s->capacity == 0) ? 1 : 2 * s->capacity;
        s->elems = realloc(s->elems, new_capacity * sizeof(stack_elem));
        if (s->elems == NULL)
        {
            printf("No se pudo asignar memoria correctamente\n");
            exit(EXIT_FAILURE);
        }
        s->capacity = new_capacity;
    }
    s->elems[s->size] = e;
    s->size += 1;
    return s;
}

stack stack_pop(stack s)
{
    assert(!stack_is_empty(s));
    s->size -= 1;
    return s;
}

unsigned int stack_size(stack s)
{
    return s->size;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s)
{
    return s->size == 0;
}

stack_elem *stack_to_array(stack s)
{
    stack_elem *arr = malloc(s->size * sizeof(stack_elem));
    assert(arr != NULL);

    for (unsigned int i = 0; i < s->size; i++)
    {
        arr[i] = s->elems[i];
    }

    return arr;
}

stack stack_destroy(stack s)
{
    free(s->elems);
    free(s);
    return NULL;
}
