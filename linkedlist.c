#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next; // Memory address for next node
}
node;

int main(int argc, char *argv[])
{
    node *head = NULL; // Head of linked list has a null pointer at the start

    int number = 0;
    n = get_int("How many numbers do you want to enter: ");

    for (int x = 0; x < n; x++)
    {
        // Allocate node for inputted number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("No value inputted.");
            return 1;
        }
    }
}