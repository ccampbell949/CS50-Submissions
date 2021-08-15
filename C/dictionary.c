// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h> 

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];
int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int wordLength = strlen(word);
    char copy[wordLength + 1]; //extra space for null character at end of string
    copy[wordLength] = '\0';
    
    for (int i = 0; i < wordLength; i++)
    {
        copy[i] = tolower(word[i]); //convert to lower case
    }

    int hashcode = hash(copy); //hash code for the copied
    node *tmp = table[hashcode];
    if (tmp == NULL)
    {
        return false; //return if pointer points to null
    }
    
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, copy) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 10000;
    
    int a = *word;
    
    while (a == *word++)
    {
        hash = ((hash << 5) + hash) + a; 
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r"); //open dictionary and read file
    if (file == NULL)
    {
        return false; //if the pointer points to null, return false
    }
    {
        char buffer[LENGTH + 1]; //buffer plus 1 for \0
        while (fscanf(file, "%s", buffer) != EOF) //scan until the end of the file
        {
            node *n = malloc(sizeof(node)); //allocate memory for n
            if (n == NULL)
            {
                fclose(file); //if points to null, return false and close file
                return false;
            }
            
            else
            {
                strcpy(n->word, buffer);
                
                n->next = NULL;
                
                unsigned int index = hash(buffer);
                
                n->next = table[index];
                table[index] = n;
                
                wordcount++;
            }
        }
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) //iterate
    {
        node *tmp1 = table[i];//tmp node in position i in array
        
        while (tmp1 != NULL) //if pointer value exists
        {
            node *tmp2 = tmp1; //temp node 2 equal to temp node 1
            tmp1 = tmp1 -> next; //pointer from tempnode 1 to next in linked list
            free(tmp2);
        }
    }
    return true;
}
