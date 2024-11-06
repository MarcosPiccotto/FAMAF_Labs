#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main()
{
    string str1 = string_create("apple");
    string str2 = string_create("banana");

    // Comparación utilizando string_less()
    if (string_less(str1, str2))
    {
        printf("%s is less than %s\n", string_ref(str1), string_ref(str2));
    }
    else
    {
        printf("%s is not less than %s\n", string_ref(str1), string_ref(str2));
    }

    // Comparación utilizando string_eq()
    if (string_eq(str1, str2))
    {
        printf("%s is equal to %s\n", string_ref(str1), string_ref(str2));
    }
    else
    {
        printf("%s is not equal to %s\n", string_ref(str1), string_ref(str2));
    }

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);

    return 0;
}
