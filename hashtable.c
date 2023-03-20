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
        string phrase = get_string("Enter phrase number %i :\n", i + 1);
        int index = hash(phrase);
        printf("%s hashes to %i\n", phrase, index);
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return 1;
        }

        newnode->phrase = phrase;
        newnode->next = NULL;
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
    node *currentnode = malloc(sizeof(node));
    currentnode = table[index];

    while (currentnode->next != NULL)
    {
        currentnode = table[index]->next;
    }
    currentnode->next = currentnode;
}

void outputTable()
{
    for (int j = 0; j < 26; j++)
    {
        printf("%c\n", table[j]->phrase[0]);
        printf("%s\n", table[j]->phrase);
    }
}