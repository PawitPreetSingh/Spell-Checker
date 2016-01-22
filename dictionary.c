/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include <string.h>

#include <cs50.h>

 typedef struct node
{
    char dict[45];
    struct node* next;
} node;

node* hashtable[26];

char array_check[26] = {0};
char word_check[46]= {0};       
char buffer[46] = {0};
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    

    int i;
    for(i = 0; word[i] != '\0'; i++)
    {
        word_check[i] = tolower(word[i]);
    }
    word_check[i] = '\0';
    int hash = hashfunction(word_check);
    if(array_check[hash] != 1)
    {
        
        return false;
    }
    else
    {
        node* ptr = hashtable[hash];
        while(ptr->next != NULL)
        {
            if(strcmp(ptr->dict, word_check) == 0)
                return true;
            ptr = ptr->next; 
         
        }
        if(ptr->next == NULL)
        {
            if(strcmp(ptr->dict, word_check) == 0)
            {
                return true;
            }   
         
        } 
     }      
 
 return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s\n", dictionary);
        
        return 1;
    }
    int c;
     
    while(!feof(file))
    {
        fscanf(file, "%s", buffer);
        if((c = fgetc(file)) == EOF)
            break;
        int hash = hashfunction(buffer);      
            if(array_check[hash] != 1)
            {
               hashtable[hash] = (node*) malloc(sizeof(node));
               strcpy((hashtable[hash]->dict) , buffer);
               hashtable[hash] -> next = NULL;
               array_check[hash] = 1;
              
            }
            
        
        else
        {
            node* new_node = (node*) malloc(sizeof(node));
            strcpy((new_node ->dict), buffer);
            node* ptr = hashtable[hash];
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }
                     
           ptr -> next = new_node; 
           new_node->next = NULL;     
        }
        
}
fclose(file);
return true;

}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int count = 0;
    for(int i = 0; i< 26; i++)
    {
        if(array_check[i] != 1)
            continue;
        node* ptr = hashtable[i];
        while(ptr->next != NULL)
        {
            if(ptr->dict[0] >= 97 && ptr->dict[0] <= 122)
            { 
                count++;
            }
            ptr = ptr->next;
        }
        if(ptr->dict[0] >= 97 && ptr->dict[0] <= 122)
        { 
                count++;
        }
        
    }
    
   
    return count;
    
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < 26; i++)
    {
        if(array_check[i] != 1)
            continue;
        node* ptr = hashtable[i];
        node* point;
        while(ptr->next != NULL)
        {
            point = ptr -> next;
            
            free(ptr);
            ptr = point;
        }
        free(ptr);
        
    } 
    
    
    return true;
}

int hashfunction(char* key)
{
    return (key[0] - 'a') % 26 ;
    
}
