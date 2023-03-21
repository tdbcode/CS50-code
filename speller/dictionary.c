// Implements a dictionary's functionality

/* Sources used:

Didn't want to read line by line for load function as it wasn't easy to identify how each word\
was without checking for \n. Easier to just read in word using:
https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm

Used this source to work out how to detect end of file in a while loop rather than if statement
which was breaking the algorithm:
https://www.tutorialspoint.com/explain-the-end-of-file-eof-with-a-c-program

*/

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

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
int dictionary_size = 0; // global variable for size of the dictionary

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //int counter = 0; // Create counter and set to 0
    int hashvalue = hash(word);
    //printf("%i\n", hashvalue); //testing purposes only

    // Go through the whole dictionary list
    for (node *currentword = table[hashvalue]; currentword != NULL; currentword = currentword->next)
    {
        //printf("%s\n", currentword->word); //testing purposes only
        // If word passed in matches the current word in the dictionary
       /* IT's ALL RETURNING TRUE*/
       if (strcasecmp(word, currentword->word) == 0)
        {
            return true;    // return true
        }
        //counter++; // add one to counter
    }

    return false; // if it gets to this point the word is not found, return false
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
    FILE *dictionary_pointer = fopen(dictionary, "r"); // Open dictionary in read mode
    // If memory was not allocated, end the program
    if (dictionary_pointer == NULL)
    {
        return false; // has to return false and not 1 as it is a boolean value and dictionary was not loaded
    }

    char word[LENGTH + 1]; // Create string to store word

    //bool lastword = false; // identifies if it's the last word
    // while word is loaded from file and saved as word
    while (fscanf(dictionary_pointer, "%s", word) != EOF)
    {
        //printf("%s\n", word); // for testing
        /* Might mean dictionary adds no wordd
        // compare if word is equal to blank, if so, exit loop as end of file
        if (strcmp(word, ""))
        {
            //lastword = true;
            break;
        }*/

        // set currentword pointer to size of node to contain pointer for current word loaded from dictionary
        node *currentword = malloc(sizeof(node));
        // If memory was not allocated, end the program
        if (currentword == NULL)
        {
            return false; // has to return false and not 1 as it is a boolean value and the word was not loaded
        }

        strcpy(currentword->word, word); // set current word to word loaded from file
        currentword->next = NULL; // set next pointer of new word to NULL
        //printf("%s\n", currentword->word); // for testing
        // have to find location in dictionary for current word so needs hash value
        int hashvalue = hash(word);
        //printf("%i\n", hashvalue); // for testing

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
        dictionary_size++; // add one to dictionary size
    }

    fclose(dictionary_pointer); // Close file
    return true; // Function complete
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size; // what is the point of this if it's a global variable?
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // for each hash in hashtable
    for (int h = 0; h < 26; h++)
    {
        // Free memory
        node *currentnode = table[h]; // load first node in hashtable

        //while current selected node is not null
        while (currentnode != NULL)
        {
            node *next = currentnode->next; // set next to current pointer for switch
            free(currentnode); // free memory for current node
            currentnode = next; // switch next to current node to continue clearing
        }
    }
    return true; // return true when complete
}
