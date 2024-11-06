#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    struct s_node **array;
    unsigned int size;
    priority_t min_priority;
};

struct s_node
{
    struct s_node *next;
    pqueue_elem elem;
};

static struct s_node *create_node(pqueue_elem e)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pqueue q)
{
    bool res = (q != NULL);
    if (res && q->size != 0)
    {
        unsigned int length = 0;
        // reccorrer el arreglo de prioridades
        for (size_t i = 0; i <= q->min_priority; i++)
        {
            // recorrer nodo por nodo para contarlos
            struct s_node *node = q->array[i];
            unsigned int c = 0;
            while (node != NULL)
            {
                node = node->next;
                c++;
            }
            length += c;
        }
        res = (length == q->size);
    }
    return res;
}

pqueue pqueue_empty(priority_t min_priority)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    // asignamos memoria dinamica
    // el tamaño de la estructura + la cantidad de elementos que tiene el arreglo
    q->array = calloc(min_priority + 1, sizeof(struct s_node *));
    q->size = 0;
    q->min_priority = min_priority;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->array[priority] == NULL)
    { // no hay pacientes con la prioridad que buscamos, asignamos automaticamente
        q->array[priority] = new_node;
    }
    else
    { // Si hay al menos un elemento, lo agregamos al final
        struct s_node *aux = q->array[priority];
        // buscamos el ultimo elemento
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new_node;
    }

    q->size += 1u;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    bool first = false;
    unsigned int i = 0;
    // buscamos el primer elemento del arreglo de prioridades que no sea nulo
    while (!first)
    {
        assert(i <= q->min_priority);
        if (q->array[i] != NULL)
        {
            first = true;
        }
        i += 1u;
    }
    assert(invrep(q));
    return (q->array[i - 1u])->elem; // i is at least 1, so i-1>=0
}

priority_t pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    bool first = false;
    unsigned int i = 0;
    while (!first)
    {
        assert(i <= q->min_priority);
        if (q->array[i] != NULL)
        {
            first = true;
        }
        i++;
    }
    assert(invrep(q));
    return i - 1; // i is at least 1, so i-1>=0
}

size_t pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    bool deleted = false;
    unsigned int i = 0;
    while (!deleted)
    {
        assert(i <= q->min_priority);
        if (q->array[i] != NULL)
        {
            struct s_node *killme = q->array[i];
            q->array[i] = q->array[i]->next;
            q->size -= 1u;
            killme = destroy_node(killme);
            deleted = true;
        }
        i++;
    }
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    struct s_node *node = NULL;
    for (size_t i = 0; i <= q->min_priority; i++)
    {
        struct s_node *killme = NULL;
        node = q->array[i];
        while (node != NULL)
        {
            killme = node;
            node = node->next;
            killme = destroy_node(killme);
        }
    }

    // free array
    free(q->array);
    q->array = NULL;

    // free the pqueue
    free(q);
    q = NULL;

    return q;
}
