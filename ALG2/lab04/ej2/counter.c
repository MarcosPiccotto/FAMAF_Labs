#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter
{
    unsigned int count;
};

counter counter_init(void)
{
    counter new = NULL;
    new = malloc(sizeof(struct _counter));
    new->count = 0;
    return new;
}

void counter_inc(counter c)
{
    c->count++;
}

bool counter_is_init(counter c)
{
    return c->count == 0;
}

void counter_dec(counter c)
{
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c)
{
    counter new = NULL;
    new = malloc(sizeof(struct _counter));
    new->count = c->count;
    return new;
}

void counter_destroy(counter c)
{
    // no puedo liberar p si es NULL
    if (c != NULL)
    {
        free(c);
    }
}
