// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 247050;

// Hash table
node *table[N];

// Save the size of the dictionary
unsigned int size_dictionary = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    /*
        [√] case insensitive

        [√] hash word to obtain hash value
        [√] access linked list at that index in the hash table
        [√] traverse linked list looking for the word (using "strcasecmp")
            [√] move a pointer from the first node to the next one until NULL
            [√] cursor = cursor->next;
            [√] start with cursor set to first item in linked list
            [√] keep moving cursor until you get to NULL, checking each node for the word
    */

    // hash word to obtain the index value
    unsigned int index = hash(word);

    // access the linked list at the index value
    node *cursor = table[index];

    // iterates through the linked list
    while (cursor != NULL)
    {
        // check if the words match
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        // update cursors
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*
        [√] input:   word, with alphabetical characters and (possibly) apostrophes
        [√] output:  numerical index between 0 and N-1, inclusive

        [√] larger N means more buckets
        [√] if your function ends up with a value greater than N, you can take the value % N o get a value in the appropriate range

            example Hash Functions
             - first letter
             - first two letters
             - math using all the letters
             - ...
    */

    // convert to lower case, and get word length
    char letter = word[0];
    int length = 0;
    unsigned int hash = 0;

    while (letter != '\0')
    {
        length++;
        hash += tolower(letter) * length;
        letter = word[length];
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    /* TODO
        [√] Open the dictionary file
            [√] Check if the file has been loaded correctly

        [√] Read each word from the dictionnary

        [√] create a new node for each word
            [√] use malloc
            [√] remember to check if retun value is NULL
            [√] copy word into node using strcpy

        [√] hash word to obtain a hash value
            [√] use the hash function
            [√] function takes a string and returns an index

        [√] insert node into his table at that location
            [√] recall that hash table is an array of linked lists
            [√] be sure to set pointers in the correct order

        [√] update the size of the dictionary
    */


    // open dictionary file
    FILE *file = fopen(dictionary, "r");

    // check if the file has been opened correctly
    if (file == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return false;
    }

    // variables
    unsigned int index = 0;

    // read words from file one at a time until EOF
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory and check for error
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // copy the word in the node
        strcpy(n->word, word);

        // hash the word to find the corresponding bucket
        index = hash(word);

        // insert the node in the linked list
        n->next = table[index];
        table[index] = n;

        // update dictionary size
        size_dictionary++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_dictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /*
        [√] iterate through the linked lists inside the hash table
        [√] free each memory allocated
            [√] use temporary cursors to keep track of nodes
            [√] move cursor to next element
            [√] free temporary
            [√] update both cursors
    */

    // iterates through all the buckets of the hash tables
    for (unsigned int i = 0; i < N; i++)
    {
        // initialise cursor
        node *cursor = table[i];

        // iterates through the linked list
        while (cursor != NULL)
        {
            // update cursors
            node *tmp = cursor;
            cursor = cursor->next;

            // free the memory
            free(tmp);
        }
    }
    return true;
}
