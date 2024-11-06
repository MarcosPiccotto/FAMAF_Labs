#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

struct _s_string
{
    char *content;
    unsigned int length;
};

string string_create(const char *word)
{
    string str = malloc(sizeof(struct _s_string));
    str->length = strlen(word);
    str->content = malloc((str->length + 1) * sizeof(char));
    strncpy(str->content, word, str->length + 1);
    return str;
}

unsigned int string_length(string str)
{
    return str->length;
}

bool string_less(string str1, string str2)
{
    return strcmp(str1->content, str2->content) < 0;
}

bool string_eq(string str1, string str2)
{
    return strcmp(str1->content, str2->content) == 0;
}

string string_clone(string str)
{
    return string_create(str->content);
}

string string_destroy(string str)
{
    if (str != NULL)
    {
        free(str->content);
        free(str);
    }
    return NULL;
}

void string_dump(string str, FILE *file)
{
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str)
{
    return str->content;
}
