#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

int hash(string phrase);
void addPhrase(node *newnode, int index);
void outputTable();

node *table[26];

int main(void)
{
    int numberOfWords = get_int("How many phrases would you like to add?");

    for (int i = 0; i < numberOfWords; i++)
    {
        string phrase = get_string("Enter phrase number %i ", i + 1);
        int index = hash(phrase);
        //printf("%s hashes to %i\n", phrase, index);
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return 1;
        }

        newnode->phrase = phrase;
        newnode->next = NULL;
        //printf("%s\n", newnode->phrase);
        addPhrase(newnode, index);
    }

   outputTable();
}

int hash(string phrase)
{
    return toupper(phrase[0]) - 'A';
}

void addPhrase(node *newnode, int index)
{
    // If first item in hash is empty then add new node
    if (table[index] == NULL)
    {
        table[index] = newnode;
        printf("Phrase added \n");
        return;
    }

    // make a current node for temporary searching linked list
    node *currentnode = malloc(sizeof(node));

    // if problem assigning memory, exit program
    if (currentnode == NULL)
    {
        return;
    }

    currentnode = table[index]; // set current node to first item in hashtable

    // while there are items in hash set current not to the next item
    while (currentnode->next != NULL)
    {
        currentnode = currentnode->next;
    }
    currentnode->next = newnode;  // when correct spot found set current node next pointer to the new node
    //printf("Phrase added \n");
}

void outputTable()
{
    // for each hash in hashtable
    for (int h = 0; h < 26; h++)
    {
        // If the current hash isn't empty
        if (table[h] != NULL)
        {
            printf("%c\n", toupper(table[h]->phrase[0])); // output letter of current hash
            // repeat until next end of that current linked list
            for (node *ptr = table[h]; ptr != NULL; ptr = ptr->next)
            {
                printf("%s\n", ptr->phrase);
            }
        }
    }
}