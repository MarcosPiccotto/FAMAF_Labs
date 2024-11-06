#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    int max, min; 
    max = min = value;
    res.is_upperbound = 0;
    res.is_lowerbound = 0; 
    res.exists = 0;
    res.where = -1;
    for (int i = 1; i < length; i++) {
        if(value == arr[i] && !res.exists){
            res.exists = 1;
            res.where = i;
        }
        if (arr[i] >= max) {
            max = arr[i];
        }
        else if (arr[i] < min) {
            min = arr[i];
        }
    }
    if (value == max) {
        res.is_upperbound = 1; 
    } else if (value == min) {
        res.is_lowerbound = 1;
    }
    return res;
}

void fillingMatrix(int arr[], unsigned int length){
    int count = 1;
    printf("ingrese %d numeros para llenar el arreglo\n", length);
    
    for (int i = 0; i < length; i++) {
        printf("Número %d: ", count);
        count++;
        scanf("%d", &arr[i]);
    }
}

void check_result(struct bound_data result){
    if(result.is_upperbound && result.exists){
        printf("El numero que ingreso es un maximo y se encuentra en la posición %d\n", result.where); // Imprime 1
        
    }
    else if(result.is_upperbound && !result.exists){
        printf("El numero que ingreso es una cota superior, pero no se encuentra en el arreglo\n"); // Imprime 1
        
    }
    else if(result.is_lowerbound && result.exists){
        printf("El numero que ingreso es un minimo  y se encuentra en la posición %d\n", result.where);
        
    }
    else if(result.is_lowerbound && !result.exists){
        printf("El numero que ingreso es una cota inferior, pero no se encuentra en el arreglo\n"); // Imprime 1
        
    }
    else{
        printf("Su numero no es relevante en nuestros parametros de busqueda\n"); // Imprime 10
    }
}

int main(void) {
    int a[ARRAY_SIZE] = {0,0,0,0};
    int value;
    fillingMatrix(a,ARRAY_SIZE);

    printf("Ingrese el numero que quiere buscar: ");
    scanf("%d",&value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);
    
    check_result(result);

    return EXIT_SUCCESS;
}

