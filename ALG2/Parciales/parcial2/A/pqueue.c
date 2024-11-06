#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;    // Tamaño de la pila
    struct s_node *first; // Puntero al primer nodo
    struct s_node *last;  // Puntero al ultimo nodo
};

struct s_node
{
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
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

static bool invrep(pqueue q)
{
    // Verificar que p1 ≤ p2 ≤ … ≤ pN, donde p es la prioridad de cada elemento
    bool res = q != NULL;
    if (res && q->size != 0 && q->first != NULL)
    {
        struct s_node *current = q->first;
        unsigned int length = 1u;
        while (current->next != NULL && res)
        {
            if (!(current->priority <= current->next->priority))
            {
                res = false;
            }
            current = current->next;
            length += 1u;
        }
        res = res && q->size == length;
    }
    return res;
}

pqueue pqueue_empty(void)
{
    pqueue q = malloc(sizeof(struct s_pqueue)); // Alojo memoria para el nodo principal
    q->size = 0;                                // Tamaño inicial en 0
    q->first = q->last = NULL;                  // Puntero al primer nodo NULL (no existe el primer nodo)
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);

    if (pqueue_is_empty(q) || priority < q->first->priority)
    {
        // Si la cola está vacía o la prioridad del nuevo nodo es menor que la prioridad del primer nodo actual
        // Insertar el nuevo nodo al principio de la cola
        new_node->next = q->first;
        q->first = new_node;
    }
    else
    {
        struct s_node *current = q->first;
        while (current->next != NULL && priority >= current->next->priority)
        {
            // Recorrer la cola hasta encontrar la posición correcta para insertar el nuevo nodo
            current = current->next;
        }
        // Insertar el nuevo nodo después del nodo actual
        new_node->next = current->next;
        current->next = new_node;
    }

    q->size += 1u;
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->first == NULL;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q)
{
    assert(invrep(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = 0u;
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = q->first;
    q->first = q->first->next;
    q->size -= 1;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    struct s_node *node = q->first;
    while (node != NULL)
    {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}