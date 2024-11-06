#include <stdio.h>
#include <stdlib.h>
#include "mybool.h"
#include "array_helpers.h"

unsigned int array_from_file(int array[],unsigned int max_size,const char *filepath) {
    
    //Abre el archivo en la ruta pasada por parametros
    FILE *fp = fopen(filepath, "r");

    // por si no encuentra el archivo
    if (fp == NULL) {
        printf("Error: could not open file '%s' for reading\n", filepath);
        exit(EXIT_FAILURE);
    }

    //Lee el largo del arreglo
    int length;
    fscanf(fp, "%d", &length);

    unsigned int count = 0;
    int num;
    // verifica si pudo leer un número, si puede lo va guardando un array
    while (fscanf(fp, "%d", &num) == 1) {
        array[count] = num;
        count++;
        if (count >= max_size) {
            printf("El largo de su arreglo es mayor a la cantidad de elementos disponible");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
    //cambio el tipo de length de int a unsigned int para que no me salga un error
    if (count != (unsigned int)length) {
        printf("La cantidad de elementos es mayor al largo indicado");
        exit(EXIT_FAILURE);
    }
    return count;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length; i++) {
        printf("%d", a[i]);
        if (i < length - 1) {
            printf(",");
        }
    }
    printf("]\n");
    printf("%s\n",array_is_sorted(a,length) ? "Su arreglo esta ordenado de forma ascendente":"Su arreglo no esta ordenado de forma ascendente");
}

mybool array_is_sorted(int a[], unsigned int length){
    mybool is_sorted = true;
    for (unsigned int i = 1; i < length; i++) {
        if (a[i] < a[i-1]) {
            is_sorted = false;
            break;
        }
    }
    return is_sorted;   
}