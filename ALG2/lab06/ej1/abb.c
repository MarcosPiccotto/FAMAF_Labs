#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb
{
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b)
{
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b)
{
    return a < b;
}

static bool izq_ord(abb_elem e, abb tree)
{
    bool izq = true;
    if (tree != NULL)
    {
        izq = elem_less(tree->elem, e) && izq_ord(e, tree->left) && izq_ord(e, tree->right);
    }
    return izq;
}

static bool der_ord(abb_elem e, abb tree)
{
    bool der = true;
    if (tree != NULL)
    {
        der = elem_less(e, tree->elem) && der_ord(e, tree->left) && der_ord(e, tree->right);
    }
    return der;
}

static bool invrep(abb tree)
{
    bool res = true;
    if (tree != NULL)
    {
        res = izq_ord(tree->elem, tree->left) && der_ord(tree->elem, tree->right) && invrep(tree->left) && invrep(tree->right);
    }

    return res;
}

abb abb_empty(void)
{
    abb tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e)
{
    assert(invrep(tree));
    abb nodo = malloc(sizeof(struct _s_abb));
    nodo->elem = e;
    nodo->left = NULL;
    nodo->right = NULL;
    if (abb_is_empty(tree))
    {
        tree = nodo;
    }
    else
    {
        abb pointer = tree;
        bool nonstop = true;
        while (nonstop)
        {
            if (elem_less(pointer->elem, e) && pointer->right != NULL)
            {
                pointer = pointer->right;
            }
            else if (elem_less(e, pointer->elem) && pointer->left != NULL)
            {
                pointer = pointer->left;
            }
            else
            {
                nonstop = false; // llego hasta la hoja
            }
        }

        if (elem_less(e, pointer->elem) && !elem_eq(e, pointer->elem)) // me fijo donde debo colocar el nuevo nodo y que no se repita
        {
            pointer->left = nodo;
        }
        else if (elem_less(pointer->elem, e) && !elem_eq(e, pointer->elem))
        {
            pointer->right = nodo;
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree)
{
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e)
{
    bool exists = false;
    assert(invrep(tree));
    if (tree == NULL)
    {
        return false;
    }
    else if (elem_less(e, tree->elem))
    {
        exists = abb_exists(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        exists = abb_exists(tree->right, e);
    }
    else if (elem_eq(e, tree->elem))
    {
        return true;
    }
    return exists;
}

unsigned int abb_length(abb tree)
{
    unsigned int length = 0u;
    assert(invrep(tree));
    if (tree != NULL)
    {
        length += 1 + abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

// funcion aux para el remove
abb del_max(abb tree)
{
    if (tree->right == NULL)
    {
        return tree->left;
    }
    else
    {
        tree->right = del_max(tree->right);
    }
    return tree;
}

abb abb_remove(abb tree, abb_elem e)
{
    assert(invrep(tree));

    if (tree == NULL)
    {
        return NULL;
    }
    else if (e < tree->elem)
    {
        tree->left = abb_remove(tree->left, e);
        return tree;
    }
    else if (e > tree->elem)
    {
        tree->right = abb_remove(tree->right, e);
        return tree;
    }
    else // e == tree->elem
    {
        if (tree->left == NULL)
        {
            abb right_subtree = tree->right;
            free(tree);
            return right_subtree;
        }
        else if (tree->right == NULL)
        {
            abb left_subtree = tree->left;
            free(tree);
            return left_subtree;
        }
        else
        {
            abb max_node = tree->left;
            while (max_node->right != NULL)
            {
                max_node = max_node->right;
            }
            tree->elem = max_node->elem;
            tree->left = del_max(tree->left);
            return tree;
        }
    }
}

abb_elem abb_root(abb tree)
{
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));

    root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree)
{
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    abb pointer = tree;
    while (pointer->right != NULL)
    {
        pointer = pointer->right;
    }
    max_e = pointer->elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree)
{
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    abb pointer = tree;
    while (pointer->left != NULL)
    {
        pointer = pointer->left;
    }
    min_e = pointer->elem;

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree)
{
    assert(invrep(tree));
    if (tree != NULL)
    {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree)
{
    assert(invrep(tree));
    if (tree == NULL)
    {
        return NULL;
    }
    tree->left = abb_destroy(tree->left);
    tree->right = abb_destroy(tree->right);
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}
