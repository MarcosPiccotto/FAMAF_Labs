#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "fixstring.h"

void swap(fixstring a[], unsigned int i, unsigned int j) {
    fixstring aux;

    // Intercambia los elementos de a[i] y a[j] uno a uno
    for (unsigned int k = 0; k < FIXSTRING_MAX; k++) {
        aux[k] = a[i][k];
        a[i][k] = a[j][k];
        a[j][k] = aux[k];
    }
}

bool goes_before(fixstring x, fixstring y) {
    // Recorre los caracteres de x e y comparándolos uno a uno
    for (unsigned int i = 0; i < FIXSTRING_MAX; i++) {
        if (x[i] < y[i]) {
            return true;
        } else if (x[i] > y[i]) {
            return false;
        }
    }
    // Si llegamos hasta aquí, x e y son iguales
    return false;
}

bool array_is_sorted(fixstring array[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before(array[i-1], array[i])) {
        i++;
    }
    return (i >= length);
}

