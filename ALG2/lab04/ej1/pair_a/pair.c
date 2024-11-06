#include "pair.h"
#include <stdlib.h> /* EXIT_SUCCESS... */
#include <stdio.h>  /* printf()...     */

pair_t pair_new(int x, int y)
{
    pair_t new;
    new.fst = x;
    new.snd = y;
    return new;
}
int pair_first(pair_t p)
{
    return p.fst;
}
int pair_second(pair_t p)
{
    return p.snd;
}
pair_t pair_swapped(pair_t p)
{
    int aux = p.fst;
    p.fst = p.snd;
    p.snd = aux;
    return p;
}

// pair_t pair_destroy(pair_t p)
// {
//     p.fst = NULL;
//     p.snd = NULL;
//     // Devolver un puntero nulo
//     return p;
// }