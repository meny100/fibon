#include <stdio.h>
#include <stdlib.h>

#define ARG_NUM 2

typedef struct item
{
    unsigned long  value;
    struct item *prev;
}item;

/*This function gets number of elements, create linked list of n fibonacci numbers and return the last one*/
item *create_fibon_sequence(int num_of_elements);
/*this func gets the pointer to the last element in the linked list and number of elements and print it to the screen descending*/
void print_fibon(item *last_fibon, int num_of_elements);
/*this func gets pointer to file and pointer to element and number of elements and write it to the file descending*/
void print_fibon_to_file(FILE *ofp, item *last_fibon, int num_of_elements);
/*get node of the linked list and the num of elements and free allocation of all items in the fibonacci sequence*/
void free_allocation(item *last_fibon, int num_of_elements);
