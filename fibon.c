#include "fibon.h"

/*this program gets file name in the arguments command line and n number from
  the user and prints the nth first fibonacci numbers to the screen and to the file, descending.
  the implementation is with linked list*/
int main(int argc, char *argv[])
{
    FILE *ofp;  /*output file pointer*/
    int num_of_fibon;
    item *last_fibon;

    if (argc == ARG_NUM) 
        if((ofp = fopen(*++argv, "w")) == NULL)
            printf("cannot open file %s.\n", *argv);
        else
        {
            printf("Enter the number of fibonacci numbers: ");
            if(scanf("%d", &num_of_fibon) != 1)
            {
                printf("Only integer allowed.\n");
                return 1;
            }
            /*create the linked list and get the last item*/
            last_fibon = create_fibon_sequence(num_of_fibon);
            if(last_fibon != NULL)
            {
                /*printing to the screen, starting from the last item*/
                print_fibon(last_fibon, num_of_fibon);
                /*writing to the file, starting from the last item*/
                print_fibon_to_file(ofp, last_fibon, num_of_fibon);
                /*free allocation*/
                free_allocation(last_fibon, num_of_fibon);
            }
        }
    else 
        {
            printf("The number of arguments name is in correct.\n");
            return 1;
        }

    return 0;
}



/*This function gets number of elements, create linked list of n fibonacci numbers and return the last one*/
item *create_fibon_sequence(int num_of_elements)
{
    item *previous = NULL, *curr = NULL, *head;
    int i;

    if (num_of_elements < 0)
    {
        printf("Fibonacci sequence is undefined for negative values.\n");
        return NULL;
    }
    
    if (num_of_elements > 46)
    {
        printf("ERROR: capacity of unsigned long is unable to contain  fibonacci grater than 46th.\n");
        return NULL;
    }

    /*create the first node and initialization*/
    curr = (item*)malloc(sizeof(item));
    if(curr == NULL)
    {
        printf("Allocation memory for Fibonacci elements Failed.\n");
        return NULL;
    }
    else
    {
        curr->value = 1;
        previous = curr;
        head = curr;
    }

    /*create the remaining elements*/
    for (i = 1; i <= num_of_elements; i++) 
    {
        curr = (item*)malloc(sizeof(item));
        if(curr == NULL)
        {
            printf("Allocation memory for Fibonacci elements Failed.\n");
            return NULL;
        }

        if(i == 1)
        {
            curr->value = 1;
            curr->prev = previous;
            previous = curr;
        }
        else
        {
            /*value of the two last element*/
            curr->prev = previous;
            curr->value = curr->prev->value + curr->prev->prev->value;
            previous = curr;
        }
    }

    /*point the head prev to the last element*/
    head->prev = curr;

    return curr;
}
/*this func gets the pointer to the last element in the linked list and print it to the screen descending*/
void print_fibon(item *last_fibon, int num_of_elements)
{
    int i;
    item *curr = last_fibon;

    for(i = num_of_elements; i >= 0 ; i--)
    {
        printf("fib(%d) %lu\n", i, curr->value);
        curr = curr->prev;
    }
}
/*this func gets pointer to file and pointer to element and write it to the file descending*/
void print_fibon_to_file(FILE *ofp, item *last_fibon, int num_of_elements)
{
    int i;
    item *curr = last_fibon;
    char *explain = "** this program gets a number from the user and prints the nth first fibonacci numbers descending to the screen and to the file given in the arg command line. the implementation is with linked list **\n\n";

    fprintf(ofp, "%s", explain);
    for(i = num_of_elements; i >= 0 ; i--)
    {
        fprintf(ofp, "fib(%d) %lu\n", i, curr->value);
        curr = curr->prev;
    }
}

/*get node of the linked list and the num of elements and free allocation of all items in the fibonacci sequence*/
void free_allocation(item *last_fibon, int num_of_elements)
{
     item *curr = last_fibon, *temp;
     while(num_of_elements-- >= 0)
     {
        temp = curr->prev;
        free(curr);
        curr = temp;
     }
}