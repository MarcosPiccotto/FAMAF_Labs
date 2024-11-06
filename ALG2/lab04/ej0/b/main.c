#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void print_data(data_t d)
{
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

void set_name(name_t new_name, data_t *d)
{
    int i;
    for (i = 0; new_name[i] != '\0'; i++)
    {
        d->name[i] = new_name[i];
    }
    d->name[i] = '\0';
}

int main(void)
{

    data_t messi = {"Leo Messi", 35, 169};
    print_data(messi);
    name_t messi_full_name = "Lionel Messi";
    /* COMPLETAR */
    data_t *messiP = NULL;
    messiP = &messi;

    set_name(messi_full_name, messiP);
    print_data(messi);

    return EXIT_SUCCESS;
}
