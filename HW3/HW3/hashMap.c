#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>
#include <string.h>
#define MAX_LOAD_FACTOR 255
/*
reminder of hashLink struct
typedef struct hashLink {
   KeyType key; the key is what you use to look up a hashLink
   ValueType value; the value stored with the hashLink, an int in our case
   struct hashLink * next; notice how these are like linked list nodes
} hashLink;
*/

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  
    
    struct hashLink *current, *last;
    int i;
    
    for(i=0; i<ht->tableSize; i++){
    
      current = ht->table[i];
      last = ht->table[i];
      
        while(current != NULL) { 
                last = current;
                current = current->next;
                free(last->key);
                free(last);
        }
    }
    
    free(ht->table);
    free(ht);
    
}


char* strDuplicate(const char* str) {
  char* dup = malloc(strlen(str)+1);
  if(dup) {
    strcpy(dup, str);
  }
  return dup;
}


/*The function insertMap() overwrites any previous value associated with the input key. */

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    int hash = stringHash2(k);
    int hashIndex = (int)(labs(hash)%ht->tableSize);
    /*char * keyCopy = strDuplicate(k);*/
    
    struct hashLink * newLink = (struct hashLink *) malloc(sizeof(struct hashLink)); /* new link to be inserted allocated*/

    assert(newLink);
    
    newLink->key = k;
    newLink->value = v; /* set up values*/
    newLink->next = ht->table[hashIndex]; /*the old index location becomes this one's next to establish linked list*/
    ht->table[hashIndex] = newLink; /*now set the old index pointer to point to this new link*/
    ht->count++; /* increase number of elements in the table */
}


/*The function atMap() returns a pointer to value associated with the input key, or returns NULL  if the key is not found.*/

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
    int hash = stringHash2(k);
    int hashIndex = (int)(labs(hash)%ht->tableSize);
    struct hashLink * indexLink = ht->table[hashIndex];

    while(indexLink != NULL) {
        if(strcmp(indexLink->key, k)==0) return &indexLink->value;
        indexLink = indexLink->next;
    }
    return NULL;
}


/*The function containsKey() returns a non-zero integer if the key is found in the hash table, and zero, otherwise.*/

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
    int hash = stringHash2(k);
    int hashIndex = (int)(labs(hash)%ht->tableSize);
    struct hashLink * indexLink = ht->table[hashIndex];
     
    while(indexLink != NULL) {
        if(!strcmp(indexLink->key, k)) { /* if the key is found, return 1 for bool ops*/
            return 1;
        }
        indexLink = indexLink->next; /*if the next is NULL, means we've hit end of bucket and break loop to return 0*/ 
    }

    return 0;
}

/*The function removeKey() removes an element with a given key from the hash table.*/


void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
    int hash = stringHash2(k);
    int hashIndex = (int)(labs(hash)%ht->tableSize);

    /* setting up links to find*/
    struct hashLink *current, *last;
    current = ht->table[hashIndex];
    last = ht->table[hashIndex];

    while(current != NULL) {
        if(current->key == k) {
            /*case if current is the first*/
            if(current == ht->table[hashIndex]){
                ht->table[hashIndex] = current->next;
            }
            /*break current out of linked list*/
            last->next = current->next;
            free(current);
            current = NULL; /*breaks loop*/
            ht->count--;
        }
        else {
            /* continue searching*/
            last = current;
            current = current->next;
        }
    }
}

/*The function sizeMap() returns the number of elements in the map.*/

int sizeMap (struct hashMap *ht)
{  /*write this*/
    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    int nullCount = 0;
    int i;
    for(i=0;i<ht->tableSize; i++) {
      if(ht->table[i]==NULL) {
        nullCount++;
      }
    }
    return nullCount;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/

    float loadFactor = ht->count/ht->tableSize;
    return loadFactor;
}
