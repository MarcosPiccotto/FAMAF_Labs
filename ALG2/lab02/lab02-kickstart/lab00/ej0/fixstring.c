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

// devuelve si true si s1 es mas chico que s2
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

