#include "strfuncs.h"
size_t string_length(const char *str)
{
    size_t cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        cont++;
    }

    return cont;
}

char *string_filter(const char *str, char c)
{
    size_t length = string_length(str);
    char *res = malloc(sizeof(char) * length);
    size_t indexAux = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != c)
        {
            res[indexAux] = str[i];
            indexAux++;
        }
    }
    res[indexAux] = '\0';
    return res;
}