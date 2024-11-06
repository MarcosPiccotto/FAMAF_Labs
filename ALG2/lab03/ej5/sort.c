/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h" 0

bool goes_before(player_t x, player_t y)
{
    if (x.rank > y.rank)
    {
        return false;
    }
    return true;
}

void swap(player_t a[], unsigned int i, unsigned int j)
{
    // guardamos un aux del jugador
    player_t aux;
    aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

bool array_is_sorted(player_t atp[], unsigned int length)
{
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i]))
    {
        i++;
    }
    return (i == length);
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der)
{
    // Establece el pivote como el elemento más a la derecha
    player_t pivot = a[der];
    // Establece i como el elemento más a la izquierda
    unsigned int i = izq;

    // recorre de izq a der
    for (unsigned int j = izq; j < der; j++)
    {
        // Si el elemento actual va antes que el pivote
        if (goes_before(a[j], pivot))
        {
            // Intercambia el elemento actual con la posición i
            swap(a, i, j);
            i++;
        }
    }
    // Intercambia el pivote con la posición i
    swap(a, i, der);

    // Retorna la posición del pivote en el arreglo
    return i;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der)
{
    if (izq < der)
    {
        unsigned int pivote = partition(a, izq, der);

        (pivote == 0u) ? quick_sort_rec(a, izq, 0u) : quick_sort_rec(a, izq, pivote - 1u);

        quick_sort_rec(a, pivote + 1u, der);
    }
}

void sort(player_t a[], unsigned int length)
{
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
