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
    int no1 = 0;
    number = get_int("How many numbers do you want to enter: ");

    for (int x = 0; x < number; x++)
    {
        // Allocate node for inputted number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("No value inputted.");
            return 1;
        }

        no1 = get_int("Enter number for node: ");
        n->number = no1;
        n->next = NULL;

        // If list is empty
        if (head == NULL)
        {
            // This node is the whole list
            head = n;
        }

        // If list has numbers already
        else
        {
            // Iterate over nodes in list
            for (node *ptr = head; ptr != NULL; ptr = ptr->next)
            {
                // If at end of list
                if (ptr->next == NULL)
                {
                    // Append node
                    ptr->next = n;
                    break;
                }
            }
        }c[p]
    }

    // Print numbers
    node *ptr = head; // current location in list
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // Free memory
    ptr = head;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}