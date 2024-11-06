/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stin(int array[],unsigned int max_size) {
    int length;
    printf("Ingrese el largo de su arreglo ");
    scanf("%d", &length);
    if((unsigned int)length > max_size){
        printf("El largo de su arreglo supera el maximo permitido\n");
        exit(EXIT_FAILURE);
    }
    
    int count = 0;
    while((unsigned int)count < (unsigned int)length) {
        printf("Ingrese el numero %d: ",count+1);
        scanf("%d",&array[count]);
        count++;
    }
    return length;
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
}


int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stin(array, MAX_SIZE);
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
