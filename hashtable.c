#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

node *table[26];

int main(void){

    int numberOfWords = get_int("How many phrases would you like to add?");

    for (int i = 0; i < numberOfWords; i++)
    {
        string phrase = get_string("Enter phrase number %i :\n", i);
        int index = hash(phrase);
        printf("%s hashes to %i\n", phrase, index);
    }
}

int hash(string phrase)
{
    return 0;
}