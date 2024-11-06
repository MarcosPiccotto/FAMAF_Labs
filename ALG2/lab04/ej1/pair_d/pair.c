#include <stdlib.h> /* EXIT_SUCCESS... */
#include <stdio.h>  /* printf()...     */
#include "pair.h"

struct s_pair_t
{
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y)
{
    pair_t new_pair = malloc(sizeof(struct s_pair_t));
    new_pair->fst = x;
    new_pair->snd = y;
    return new_pair;
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
