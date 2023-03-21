// Implements a dictionary's functionality

/* Sources used:

Didn't want to read line by line for load function as it wasn't easy to identify how each word\
was without checking for \n. Easier to just read in word using:
https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm

Rather than using bool lastword replaced this with !=EOF in while function as it fulfils that purpose:
https://www.tutorialspoint.com/explain-the-end-of-file-eof-with-a-c-program

*/

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>

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
        return false; // has to return false and not 1 as it is a boolean value and dictionary was not loaded
    }

    string word = NULL;  // Create string to store word

    //bool lastword = false; // identifies if it's the last word
    // while word is loaded from file and saved as word
    while(fscanf(dictionary_pointer, "%s", word) != EOF)
    {
        if (strcmp(word,""))
        {
            //lastword = true;
            break;
        }
        node *currentword = malloc(sizeof(node)); // set currentword pointer to size of node to contain pointer for current word loaded from dictionary
        // If memory was not allocated, end the program
        if (currentword == NULL)
        {
            return false; // has to return false and not 1 as it is a boolean value and the word was not loaded
        }

        currentword->n = word; //set current word to word loaded from file
        // have to find location in dictionary for current word so needs hash value
        int hashvalue = hash(word);

        // If the first item in the table at that hashvalue is empty
        if (table[hashvalue] == NULL)
        {
            table[hashvalue] = currentword; // Set first item to currentword
        }
        else
        {
            currentword->next = table[hashvalue]; // Otherwise point the current item's next pointer to that value
            table[hashvalue] = currentword; // then replace the first item
        }

    }

    fclose(dictionary_pointer); // Close file
    return true; // Function complete
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
