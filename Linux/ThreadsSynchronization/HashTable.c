#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int size;


struct pair{
int key;
char value[50];
};
struct pair* hashTable;
int hashFunction(int key)
{
   return key % size;

}

int isEmpty()
{
   pthread_mutex_lock(&mutex);
   for(int i = 0 ; i < size ; i++)
   {
       if(hashTable[i].key != INT_MAX)
           return 0;
   }	
   pthread_mutex_unlock(&mutex);
   return 1;

}
int findCorectPosition(int hashValue , int key)
{
   if(hashTable[hashValue].key == key)
   {
      
      return hashValue;
   }
   else
   {
      for(int i = hashValue + 1 ; i < size ; i++)
      {
          if(hashTable[i].key == key)
          {
          	
      		return i;
          }
      }
   }
   return size;
}

void* insert(void* p)
{
   struct pair item = *(struct pair*)p;
   int hashValue = hashFunction(item.key);
   pthread_mutex_lock(&mutex);
   if(hashTable[hashValue].key == INT_MAX)
   {
      
      hashTable[hashValue] = item;
   }
   else
   {
      for(int i = hashValue + 1 ; i < size ; i++)
      {
          if(hashTable[i].key == INT_MAX)
          {
          	
      		hashTable[i] = item;
      		//printf("Element inserted at %d\n" , i);
      		pthread_mutex_unlock(&mutex);
      	        return NULL;
          }
      }
   }
      
      
   
   pthread_mutex_unlock(&mutex);

}



void* getElement(void* key)
{
   int hashValue = hashFunction(*(int*)key);
   pthread_mutex_lock(&mutex);
   int corectPosition = findCorectPosition(hashValue , *(int*)key);
   if(corectPosition < size)
      printf("Element found %s\n" , hashTable[corectPosition].value);
   else
      printf("Element not found\n");
   struct pair* result = &hashTable[corectPosition];
   pthread_mutex_unlock(&mutex);
   return (void*)result;
}

void* delete(void* key)
{

   int hashValue = hashFunction(*(int*)key);
   pthread_mutex_lock(&mutex);
   int corectPosition = findCorectPosition(hashValue , *(int*)key);
   
   if(corectPosition < size)
   {
   	printf("Element deleted %s\n" , hashTable[corectPosition].value);
   
   	hashTable[corectPosition].key = INT_MAX; 
   
   }
   pthread_mutex_unlock(&mutex);
}

void printHashTable()
{
   pthread_mutex_lock(&mutex);
   for(int i = 0 ; i < size ; i++)
   {
      if(hashTable[i].key != INT_MAX)
      {
         printf("position %d has value %s\n" , i , hashTable[i].value);
      }
   }
   pthread_mutex_unlock(&mutex);
}

int main()
{
    size = 1000;
    hashTable = (struct pair*)malloc(sizeof(struct pair) * size);
    for(int i = 0 ; i < size ; i++)
    {
       hashTable[i].key = INT_MAX;
    }
    /*hashTable[0].key = 1;
    strcpy(hashTable[0].value , "mihnea");
    struct pair temp;
    temp.key = 1;
    strcpy(temp.value , "alex");
    insert((void*)&temp);*/
    
    pthread_t thread[10];
    for(int i = 0 ; i < 10 ; i++)
    {
        
       int function = rand() % 2;
       struct pair temp;
       if(function == 0)
       {
          printf("Insert key\n");
          
          scanf("%d" , &temp.key);
          printf("Insert value\n");
          scanf(" %s" , temp.value);
          pthread_create(&thread[i] , NULL , insert , (void*)&temp);
       }
       if(function == 1)
       {
          printf("Insert key\n");
          scanf("%d" , &temp.key);
          pthread_create(&thread[i] , NULL , delete , (void*)&temp.key);
          
       }
    }
    for(int i = 0 ; i < 10 ; i++)
    {
       pthread_join(thread[i] , NULL);
    }
    printHashTable();
    return 0;
}
