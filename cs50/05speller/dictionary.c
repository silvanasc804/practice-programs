// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int dict_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *list = table[hash(word)];
    if (list == NULL)
    {
        return false;
    }

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a numerical index between 0 and N - 1
unsigned int hash(const char *word)
{
    int prime = 31;
    unsigned long hash;
    hash = 5381;

    for (int i = 0; word[i] != '\0'; i++)
    {
        // Sumamos el valor ASCII de cada letra, considerando también mayúsculas/minúsculas
        if (word[i] != '\'')
        {
            hash = ((hash << 5) + hash) + tolower(word[i]);
        }
    }
    hash = hash % N;
    hash = (hash >= 0) ? hash : (hash + N);
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dictr = fopen(dictionary, "r");
    if (dictr == NULL)
    {
        return false;
    }

    // Initializes each position on the table to null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    // Read each word in the file
    while (fscanf(dictr, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash word to obtain a hash value to the linked list
        unsigned int index = hash(word);

        // Insert node into a hash table at that location, there are 2 options, for the sake of
        // order I´ll take the one that appends the word at the end of the list
        new_node->next = table[index]; // Prepend node to list
        table[index] = new_node;
        dict_words++;
    }
    fclose(dictr);
    // Close the dictionary file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
