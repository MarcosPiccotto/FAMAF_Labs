#include <stdlib.h> /* EXIT_SUCCESS... */
#include <stdio.h>  /* printf()...     */
#include "pair.h"

pair_t pair_new(int x, int y)
{
    pair_t new = NULL;
    new = malloc(sizeof(pair_t));
    new->fst = x;
    new->snd = y;
    return new;
}

int pair_first(pair_t p)
{
    return p->fst;
}
int pair_second(pair_t p)
{
    return p->snd;
}
pair_t pair_swapped(pair_t p)
{
    // creo otro par ya que sino se rompe el free(toma como si fueran iguales)
    pair_t new = pair_new(p->snd, p->fst);
    return new;
}

pair_t pair_destroy(pair_t p)
{
    // no puedo liberar p si es NULL
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }

    return p;
}
