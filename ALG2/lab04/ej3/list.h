#include <stdbool.h>

typedef int list_elem;

typedef struct Node
{
    list_elem elem;
    struct Node *next;
} Node;

typedef Node *list;

/* Constructors */

list empty();

list addl(list l, list_elem elem);

void destroy(list l);

/* Operations */

bool is_empty(list l);

list_elem head(list l);

list tail(list l);

list addr(list l, list_elem elem);

unsigned int length(list l);

list concat(list l1, list l2);

list_elem index(list l, unsigned int n);

list take(list l, unsigned int n);

list drop(list l, unsigned int);

list copy_list(list l1);
