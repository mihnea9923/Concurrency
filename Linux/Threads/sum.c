#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define CPU 4
int array[16] = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16};
int arraySize = sizeof(array) / 4;
void* partiallySum(void* start)
{
   int* startIndex = (int*) start; 
   int* sum = (int*)malloc(sizeof(int));
   *sum = 0;
   for(int i = *startIndex ; i < *startIndex + arraySize/CPU ; i++)
   {
   	*sum += array[i];
   }
   printf("Sum is %d\n" , *sum);
   return (void*)sum;
}

int main()
{
   
   int sum = 0;
   
   int partition = arraySize / CPU;
   pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * CPU);
   for(int i = 0 ; i < CPU ; i++)
   {
   	int* start = (int*)malloc(sizeof(int));
   	*start = i * partition;
   	pthread_create(&threads[i] , NULL , partiallySum , (void*)start);
   }
   	
   for(int i = 0 ; i < CPU ; i++)
   {
   	int* partialSum = (int*)malloc(sizeof(int));
   	
   	pthread_join(threads[i] , (void*)&partialSum);
   	sum += *partialSum;
   	free(partialSum);
   }
   printf("Total sum is %d\n" , sum);
    return 0;
}
