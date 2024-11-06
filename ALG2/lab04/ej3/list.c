#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

list empty()
{
    list lst = malloc(sizeof(list));
    lst = NULL;
    return lst;
}

list addl(list l, list_elem elem)
{
    Node *new_node = malloc(sizeof(Node)); // Asignar memoria para el nuevo nodo
    new_node->elem = elem;                 // Asignar el elemento al nuevo nodo
    new_node->next = l;                    // Establecer el siguiente puntero del nuevo nodo al primer nodo actual

    return new_node;
}

void destroy(list l)
{
    if (is_empty(l))
    {
        free(l);
    }
}

bool is_empty(list l)
{
    return l == NULL;
}

list_elem head(list l)
{
    assert(!is_empty(l));
    return l->elem;
}

list tail(list l)
{
    assert(!is_empty(l));
    Node *p = l;
    l = l->next;
    free(p);
    return l;
}

list addr(list l, list_elem elem)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->elem = elem;
    new_node->next = NULL;
    if (!is_empty(l))
    {
        Node *p = l;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_node;
    }
    else
    {
        l = new_node;
    }
    return l;
}

// ver si estan bien

// Función para obtener el número de elementos de una lista
unsigned int length(list l)
{
    unsigned int count = 0;
    Node *p = l;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

list concat(list l1, list l2)
{
    if (is_empty(l1))
    {
        return l2;
    }
    Node *p = l1;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = l2;
    return l1;
}

list_elem index(list l, unsigned int n)
{
    assert(n < length(l));
    Node *p = l;
    for (unsigned int i = 0; i < n; i++)
    {
        p = p->next;
    }
    return p->elem;
}

list take(list l, unsigned int n)
{
    assert(n <= length(l));
    if (n == 0)
    {
        return empty();
    }
    Node *new_node = malloc(sizeof(Node));
    new_node->elem = l->elem;
    new_node->next = take(l->next, n - 1);
    return new_node;
}

list drop(list l, unsigned int n)
{
    assert(n <= length(l));
    if (n == 0)
    {
        return l;
    }
    Node *p = l;
    for (unsigned int i = 0; i < n - 1; i++)
    {
        p = p->next;
    }
    Node *new_head = p->next;
    p->next = NULL;
    destroy(l);
    return new_head;
}

list copy_list(list l1)
{
    Node *new_head = malloc(sizeof(Node));
    new_head->elem = l1->elem;
    new_head->next = NULL;
    Node *p = l1->next;
    Node *q = new_head;
    while (p != NULL)
    {
        Node *new_node = malloc(sizeof(Node));
        new_node->elem = p->elem;
        new_node->next = NULL;
        q->next = new_node;
        p = p->next;
        q = q->next;
    }
    return new_head;
}
