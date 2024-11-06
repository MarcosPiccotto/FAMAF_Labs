/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

abb abb_from_file(const char *filepath)
{
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1)
    {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size)
    {
        abb_elem elem;
        res = fscanf(file, " %d ", &(elem));
        if (res != 1)
        {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

        ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /* dumping the tree */
    abb_dump(tree);
    printf("\n");

    if (abb_is_empty(tree))
    {
        printf("\nÁrbol vacío\n");
    }
    else
    {
        printf("1 - Mostrar árbol por pantalla\n");
        printf("2 - Agregar un elemento\n");
        printf("3 - Eliminar un elemento\n");
        printf("4 - Chequear existencia de elemento\n");
        printf("5 - Mostrar longitud del árbol\n");
        printf("6 - Mostrar raiz, máximo y mínimo del árbol\n");
        printf("7 - Salir\n");
        // ciclo infinito
        while (1)
        {
            int option;
            printf("\n");
            printf("Ingrese una opción: ");
            printf("\n");
            if (scanf("%d", &option) != 1)
            {
                fprintf(stderr, "Opcion invalida.\n");
                break;
            }
            switch (option)
            {
            case 1:
            {
                printf("\n");
                abb_dump(tree);
                break;
            }
            case 2:
            {
                printf("Ingrese el elemento a agregar: ");
                fflush(stdout);
                int element;
                if (scanf("%d", &element) != 1)
                {
                    fprintf(stderr, "ELemento invalido.\n");
                    break;
                }
                tree = abb_add(tree, element);
                break;
            }
            case 3:
            {
                printf("Ingrese el elemento a eliminar: ");
                fflush(stdout);
                int element;
                if (scanf("%d", &element) != 1)
                {
                    fprintf(stderr, "ELemento invalido.\n");
                    break;
                }
                tree = abb_remove(tree, element);
                break;
            }
            case 4:
            {
                printf("Ingrese el elemento a buscar: ");
                fflush(stdout);
                int element;
                if (scanf("%d", &element) != 1)
                {
                    fprintf(stderr, "ELemento invalido.\n");
                    break;
                }
                if (abb_exists(tree, element))
                {
                    printf("El elemento %d existe en el árbol.\n", element);
                }
                else
                {
                    printf("El elemento %d no existe en el árbol.\n", element);
                }
                break;
            }
            case 5:
            {
                printf("Longitud del árbol: %u\n", abb_length(tree));
                break;
            }
            case 6:
            {
                printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree), abb_min(tree), abb_max(tree));
                break;
            }
            case 7:
            {
                printf("Saliendo...\n");
                tree = abb_destroy(tree);
                exit(EXIT_SUCCESS);
            }
            default:
            {
                fprintf(stderr, "Opcion Invalida.\n");
                break;
            }
            }
        }
    }

    return EXIT_SUCCESS;
}
