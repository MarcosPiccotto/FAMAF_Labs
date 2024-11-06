#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length)
{
    printf("\"");
    for (unsigned int j = 0u; j < length; j++)
    {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size)
{
    FILE *file;
    unsigned int count = 0;

    file = fopen(path, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    while (!feof(file) && count < max_size)
    {
        unsigned int index;
        char letter;
        fscanf(file, "%u -> *%c* ", &index, &letter);
        indexes[count] = index;
        letters[count] = letter;
        count++;
    }
    fclose(file);

    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Debe proporcionar la ruta del archivo de entrada.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = 0;

    char *path = argv[1];
    length = data_from_file(path, indexes, letters, MAX_SIZE);

    for (unsigned int i = 0; i < length; i++)
    {
        if (indexes[i] > length || indexes[i] < 0)
        {
            perror("Hay un problema con los indices");
            exit(EXIT_FAILURE);
        }
        else
        {
            sorted[indexes[i]] = letters[i];
        }
    }

    printf("Letras desordenadas: ");
    dump(letters, length);
    printf("Letras ordenadas: ");
    dump(sorted, length);

    return EXIT_SUCCESS;
}
