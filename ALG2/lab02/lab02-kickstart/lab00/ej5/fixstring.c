#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    int length = 0;
    while (s[length] != '\0'){
        ++length;
    }
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    return s1 == s2;
}

// devuelve si true si, s1 es mas chico que s2
bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = true;
    bool firstLetterEq = s1[0] == s2[0];
    if(fstring_length(s1) < fstring_length(s2) && firstLetterEq){
        res = true;
    }
    else if(fstring_length(s1) > fstring_length(s2) && firstLetterEq){
        res = false;
    }
    else{
        for (unsigned int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++){
            if(s2[i] < s1[i]){
                res = false;
                break;
            }else{
                res = true;
                break;
            }
        }
    }
    return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

// cambia de lugar dos string ej ["hola","chau","perro"] -> ["chau","hola","perro"] 
void fstring_swap(fixstring s1, fixstring s2) {
    fixstring aux;
    fstring_set(aux,s1);
    fstring_set(s1,s2);
    fstring_set(s2,aux);
}


