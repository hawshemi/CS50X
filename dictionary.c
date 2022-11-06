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
}
node;

// Number of buckets in hash table
// hash table size = 2^16
const unsigned int N = 65536;

// Hash table
node *table[N];

// intialising another integer variable

unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // initialise the word and make it lower case
    int word_length = strlen(word);
    char lowercase[word_length + 1];
    // iterate through each character in the string

    for (int i = 0; i < word_length; i++)
    {
        lowercase[i] = tolower(word[i]);
    }
    lowercase[word_length] = '\0';

    // set cursor to appropriate linked list
    node *cursor = table[hash(lowercase)];
    // check if number of characters is 1
    if (word_length == 1)
    {
        return true;
    }
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // point cursor to the nect node
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // As we are allowed to use any hash function on the internet, I'm citing one source here
    // https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
    unsigned int hash = 0;
    // found on reddit
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *dictionary_file = fopen(dictionary, "r");
    /// reading strings from dictionary file
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        node *word_node = malloc(sizeof(node));

        if (word_node == NULL)
        {
            // unload (free) the memory
            unload();
            // return false
            return false;
        }
        else
        {
            // copying word into the word node
            strcpy(word_node->word, word);
            /// n is the hash word the word
            int n = hash(word_node->word);

            /// Point the word node to the first element of the already existing bucket in the hash_table.
            word_node->next = table[n];

            /// Point the hash table to the new node which was made.
            table[n] = word_node;
            word_count++;
        }
    }
    /// close the file
    fclose(dictionary_file);
    // return true if successful operation
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // return wordcount
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate through hashtable
    for (int i = 0; i < N; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];

        // traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        // if cursor is at the end of the linked list, free cursor itself.
        free(cursor);
    }
    return true;
    // This function makes sure you aren't leaking any memory
}
