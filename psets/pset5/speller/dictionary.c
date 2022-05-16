// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];

//Number of Words loaded in hash table
int numWordsDict = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    do
    {
        if (cursor == NULL)
        {
            return false;
        }
        if (strcasecmp((cursor->word), word) == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }
    while (cursor != NULL);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html and helped by Reddit: https://www.reddit.com/r/C_Programming/comments/2syijd/understanding_this_hash_function/
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = hash * 33 + tolower(c);
    }
    return hash % N;



    //Original Hash:
    /*// Find length
    int length = (strlen(word) - 1);

    // Make Chars
    int firstChar = 97;
    int secondChar = 97;
    int thirdChar = 97;

    // Convert to lower
    firstChar = tolower(firstChar);
    secondChar = tolower(secondChar);
    thirdChar = tolower(thirdChar);

    // Store Chars
    firstChar = word[0];

    if(length >= 2)
    {
        secondChar = word[1];

        if(length >= 3)
        {
            thirdChar = word[2];
        }
    }

    // Check not lower than 97 (colens, ect)
    if (firstChar < 97)
    {
        firstChar = 97;
    }
    if (secondChar < 97)
    {
        secondChar = 97;
    }
    if (thirdChar < 97)
    {
        thirdChar = 97;
    }

    // Return Hash value
    return ((firstChar - 97) + (secondChar - 97) + (thirdChar - 97));
    */
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Clear Table
    /*for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }*/

    // Open Dictionary and check if it's NULL
    FILE *dFile = fopen(dictionary, "r");
    if (dFile == NULL)
    {
        return false;
    }

    // Read Strings from dictionary file
    int end;
    do
    {
        // Save current word from dictionary temporarily
        char word[LENGTH + 1];
        end = fscanf(dFile, "%s", word);
        if (end == EOF)
        {
            break;
        }

        // Copy word into temp node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Malloc error
            fclose(dFile);
            return false;
        }
        strcpy(n->word, word);

        // Find into which bucket this word belongs
        int index = hash(word);
        numWordsDict++;

        //Put work in hash table
        if (table[index] == NULL)
        {
            n->next = NULL;
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }
    while (end != EOF);
    fclose(dFile);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numWordsDict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Repeat for each spot in array
    for (int i = 0; i < N; i ++)
    {
        node *cursor = NULL;
        do
        {
            if (table[i] == NULL)
            {
                free(table[i]);
                break;
            }
            else
            {
                cursor = table[i];
                node *temp = cursor;
                table[i] = cursor->next;
                free(temp);
            }
        }
        while (cursor != NULL);
    }
    return true;
}
