#include <stdio.h>
#include <stdlib.h>
 #include <time.h>
#include <pthread.h>
int elementToFind = 93;
int threadsNumber;
int arraySize;
int* array;
int threadElements , restElements;

void merge(int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[n1], R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];
 
 
    int i = 0;
 
    int j = 0;
 
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int l,int r){
    if(l>=r){
        return;
    }
    int m = (l+r-1)/2;
    mergeSort(l,m);
    mergeSort(m+1,r);
    merge(l,m,r);
}


int binarySearch(int l , int r) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        
        if (array[mid] == elementToFind) 
            return mid; 
        if (array[mid] > elementToFind) 
            return binarySearch(l, mid - 1); 
  
        return binarySearch(mid + 1, r); 
    } 
  
    return -1; 
}

void* binarySearchThread(void* arg)
{
    int index = *(int*)arg;
    int start = index * threadElements;
    int end = start + threadElements;
    if(index == threadsNumber - 1)
    {
    	end += restElements;
    }
    
   int position = binarySearch(start , end - 1);		
   if(position != -1)
   {
       printf("Position is %d\n" , position);
   }
   
   int* positionPointer = (int*)malloc(sizeof(int));
   *positionPointer = position;
   return (void*)positionPointer;
}

int main(int argc , char* argv[])
{
    
    arraySize = rand() % 1000;
    threadsNumber = 4;
    array = (int*)malloc(sizeof(int) * arraySize);
    for(int i = 0 ; i < arraySize ; i++)
    {
       array[i] = rand() % 100;
    }
    mergeSort(0 , arraySize - 1);
   
    threadElements = arraySize / threadsNumber;
    restElements = arraySize % threadsNumber;
    pthread_t threads[threadsNumber];
    
    int* threadParameter = (int*)malloc(sizeof(int) * threadsNumber);
    for(int i = 0 ; i < threadsNumber ; i++)
    {
    	threadParameter[i] = i;
       pthread_create(&threads[i] , NULL , binarySearchThread , &threadParameter[i]);
    
    }

    		
    for(int i = 0 ; i < threadsNumber ; i++)
    {
       pthread_join(threads[i] , NULL);
    
    }	
  

}
