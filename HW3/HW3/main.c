#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.

 when there are no more words in the input file this function will return NULL.

 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {

    FILE * file = fopen(argv[1],"r");
    /*Write this function*/
    int i;
    char* key;
    struct hashLink * oldLink;
    int* incrementPointer;
    struct hashMap * ht = (struct hashMap*) malloc(sizeof(struct hashMap));
    
    
    assert(file != NULL);
    
    initMap(ht, 12);

    
    key = getWord(file);
    while(key != NULL) {
      
      /*oldLink = ht->table[hashIndex];*/
  
      if(!containsKey(ht, key)) {
          insertMap(ht, key, 1);
      }
      else {
        incrementPointer = atMap(ht, key);
        if(incrementPointer != NULL) {
          *incrementPointer = *incrementPointer + 1;
        }
        free(key);
      }
      key = getWord(file);
    }
    
    for(i = 0; i < ht->tableSize; i++) {
      oldLink = ht->table[i];
      if(oldLink != NULL) {
        printf("%s : %d \n ",oldLink->key,oldLink->value);
        while(oldLink->next != NULL) {
          printf("%s : %d \n ",oldLink->next->key,oldLink->next->value);
          oldLink=oldLink->next;
        }
      }
      else {
        /*printf("%s | %d\n", "NULL",i);*/
      }
    }
    
    freeMap(ht);
    
    fclose(file);
    
    
    
    return 1;
    
}


char* getWord(FILE *file)
{

	int length = 0;
	int maxLength = 16;
	char character;

	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}

	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

