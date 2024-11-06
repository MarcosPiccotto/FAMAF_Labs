#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    //Establece el pivote como el elemento más a la derecha
    int pivot = a[der];
    //Establece i como el elemento más a la izquierda
    unsigned int i = izq;

    //recorre de izq a der
    for (unsigned int j = izq; j < der; j++) {
        //Si el elemento actual va antes que el pivote
        if (goes_before(a[j], pivot)) {
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


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    if (izq < der) {
        unsigned int pivote = partition(a, izq, der);
    
        (pivote==0u) ? quick_sort_rec(a, izq, 0u) : quick_sort_rec(a, izq, pivote-1u);

        quick_sort_rec(a, pivote + 1u, der);

    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

