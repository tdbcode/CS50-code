// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // create memory location for loading dictionary
    FILE *dictionary_pointer = fopen(dictionary, "r"); // Open dictionary passed in, in read mode
    // If memory was not allocated, end the program
    if (dictionary_pointer == NULL)
    {
        return 1;
    }

    string word = "";  // Create string to store word

    while(fscanf(dictionary_pointer, %s, word))
    {
        node *currentword = malloc(sizeof(node)); // set currentword pointer to size of node to contain pointer for current word loaded from dictionary
        // If memory was not allocated, end the program
        if (currentword == NULL)
        {
            return 1;
        }

        currentword->n = word; //set current word to word loaded from file
        // have to find location in dictionary for current word so needs hash value
        int hashvalue = hash(word);

        if (table[hashvalue] == NULL)
        {
            table[hashvalue] = currentword;
        }
        else if()

    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
