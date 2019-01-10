// Implements a dictionary's functionality
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

//declare a variable to check if the dictionary is loaded into memory
bool loaded;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        //malloc a node * for each new word
        node *new_node = malloc(sizeof(node));
        //if malloc() failed
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        //copy word into new_node
        strcpy(new_node->word, word);

        //run a word through a hash() function to return a value 0-25
        int bucket = hash(word);

        //insert new_node into a linked list
        new_node->next = hashtable[bucket];
        hashtable[bucket] = new_node;
    }

    // Close dictionary
    fclose(file);

    //dictionary is loaded into memory
    loaded = true;
    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //declare a counter
    unsigned int counter;
    //if the dictionary is loaded (return number of words counter)
    if (loaded == 1)
    {
        //set counter of words to 0
        counter = 0;
        //iterate over all buckets in a hash table
        for (int i = 0; i < N; i++)
        {
            node *ptr = hashtable[i];
            //iterate over all elements in a linked list
            while (ptr != NULL)
            {
                ++counter;
                ptr = ptr->next;
            }
        }
    }
    //else return 0
    else
    {
        return 0;
    }

    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *cursor = hashtable[hash(word)];
    while (cursor != NULL)
    {
        int i = 0;
        //buffer to copy a word into (+1 because of '/0' at the end)
        char wordcopy[strlen(word) + 1];
        //copy 'word' to make it lowercase since it is read-only
        strcpy(wordcopy, word);
        //make every char in a word lowercase
        while (wordcopy[i])
        {
            wordcopy[i] = tolower(word[i]);
            i++;
        }

        //compare the provided word with the dictionary
        if (strcmp(wordcopy, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // create a (node *) pointer cursor to point at the same node our head is pointing at
        node *cursor = hashtable[i];

        //free a linked list at each bucket
        while (cursor != NULL)
        {
            hashtable[i] = NULL;
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    //check the number of words in the dictionary
    if (size())
    {
        return false;
    }
    else
    {
        //dictionary was erased from memory
        loaded = false;
        return true;
    };

}


