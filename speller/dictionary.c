// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27 * 2000;

// Hash table
node *table[N] = {NULL};

int word_counter = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word
    int word_hash = hash(word);

    node *ptr = table[word_hash];
    // Search the table
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] != '\'')
        {
            if (i == 0)
            {
                hash_value = hash_value + (tolower(word[i]) - 'a') * 500;
            }
            else if (i == 1)
            {
                hash_value = hash_value + (tolower(word[i]) - 'a') * 200;
            }
            else if (i == 2)
            {
                hash_value = hash_value + (tolower(word[i]) - 'a') * 50;
            }
            else
            {
                hash_value = hash_value + tolower(word[i]) - 'a';
            }
        }
        else
        {
            hash_value += 26;
        }
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // Read each word in the file
    char new_word[LENGTH];
    node *n;
    while (fscanf(source, "%s", new_word) != EOF)
    {
        // Hash the word
        int word_hash = hash(new_word);

        // Create a new node
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, new_word);

        // Insert the new node into table
        n->next = table[word_hash];
        table[word_hash] = n;
        word_counter++;
    }
    // Close the dictionary table
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
