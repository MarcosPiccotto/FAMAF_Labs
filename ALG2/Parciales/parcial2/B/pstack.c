#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack
{
    unsigned int size;
    struct s_node *front;
    struct s_node *back;
};

struct s_node
{
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node *create_node(pstack_elem e, priority_t priority)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    new_node->priority = priority;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pstack s)
{
    // me tengo que fijar si el length si es correcto, si es nulo o no y si es p1>= p2 >= p3 >= p4
    bool res = s != NULL;
    if (res && s->size != 0 && s->front != NULL)
    {
        struct s_node *current = s->front;
        unsigned int length = 1u;
        while (current->next != NULL && res)
        {
            if (!(current->priority >= current->next->priority))
            {
                res = false;
            }
            current = current->next;
            length += 1u;
        }
        res = res && length == s->size;
    }
    return res;
}

pstack pstack_empty(void)
{
    pstack s = malloc(sizeof(struct s_pstack));
    s->size = 0; // Tamaño inicial en 0
    s->front = s->back = NULL;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);

    // en el caso que este vacia y/o en el caso que sea >= al de mayor prioridad
    if (pstack_is_empty(s) || priority >= s->front->priority)
    {
        new_node->next = s->front;
        s->front = new_node;
    }
    else
    {
        // el caso donde tengo que buscar donde esta su lugar
        struct s_node *current = s->front;
        while (current->next != NULL && priority < current->next->priority)
        {
            current = current->next;
        }
        // Encontre un lugar para colocar mi elemento}
        new_node->next = current->next;
        current->next = new_node;
    }
    s->size += 1u;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s)
{
    assert(invrep(s));
    return s->front == NULL;
}

pstack_elem pstack_top(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->priority;
}

unsigned int pstack_size(pstack s)
{
    assert(invrep(s));
    unsigned int size = 0;
    size = s->size;
    return size;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *killme = s->front;
    s->front = s->front->next;
    s->size -= 1;
    killme = destroy_node(killme);
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s)
{
    assert(invrep(s));
    struct s_node *node = s->front;
    while (node != NULL)
    {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
