// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include <stdlib.h>
#include <strings.h>
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
node *table[26]; //node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index;
    node *cursor;

    // Hash word to obtain a hash value
    index = hash(word);

    cursor = table[index];
    // Traverse liked list, lookin for the word
    while (cursor != NULL)
    {
        if (!strcasecmp(cursor->word, word))
        {
            //printf("%s __ %s\n",cursor->word, word);
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file;
    char word[LENGTH + 1];
    node *new;
    int index;

    // Open dictionary file
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Coud not open %s.", dictionary);
        return false;
    }
    // Read strings from file one a time
    while (fscanf(file, "%s", word) == 1)
    {
        // Create a new node for each word
        new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Allocate memory failed");
            return false;
        }
        _strcpy(new->word, word);
        new->next = NULL;
        // Hash word to obtain a hash value
        index = hash(word);
        // Insert node into hash table at that location
        if (table[index] == NULL)
        {
            table[index] = new;
        }
        else
        {
            new->next = table[index]->next;
            table[index]->next = new;
        }
        //printf("%s %i\n", word, index);
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int i = 0;
    int count = 0;
    node *current;

    while (i < N)
    {
        current = table[i];
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        i++;
    }
    //printf("%i\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i = 0;
    node *cursor, *tmp;

    while (i < N)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        i++;
    }

    return true;
}

/**
  * _strcpy - copy string from src to dest
  * @src: source string
  * @dest: dest memory
  * Return: pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
    int i;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}
