/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

	int *p1 = NULL;
	person_t *p2 = NULL;

	p1 = &x;
    *p1 = 9;
    printf("x = %d\n", x);
    /*----------------------*/
    p2 = &m;
    p2->age = 100;
    p2->name_initial = 'F';
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    /*----------------------*/
    p1 = &a[1];
    *p1 = 42;
    printf("a[1] = %d\n", a[1]);
    return EXIT_SUCCESS;
}

