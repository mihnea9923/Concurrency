#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>
#define CPU 4
int array[1000000];

int *result; 
int value = 1;

void findAllOccurences(int start, int end, int fd[2])
{

    int* occurences = (int*)malloc(sizeof(end - start + 1) * 4); 
    
    int size = 0;
    
    for (int i = start; i <= end; i++)
    {
        if (array[i] == value)
        {
            occurences[size] = i;
            size++;
        }
    }
    close(fd[0]);
    
    if(write(fd[1] , occurences , sizeof(int) * size) == -1)
    {
   	return;
    }
   close(fd[1]);
}

int main()
{
    
    int fd[2];
    srand(time(NULL));
    for(int i = 0 ; i < 1000000 ; i++)
    {
        array[i] = rand() % 100;
    }
    int arraySize = sizeof(array) / 4;
    result = (int*)malloc(sizeof(int) * arraySize);
    int processesNumber = CPU;
    int processElementsAssigned = arraySize / processesNumber;
    scanf("%d" , &value);
   
    int rest = arraySize % processesNumber;
    if (pipe(fd) == -1)
    {
        return 1;
    }
   
    
    for (int i = 0; i < CPU; i++)
    {
       
        pid_t id = fork();
        int start = i * processElementsAssigned;
        int end = start + processElementsAssigned - 1;
        if (rest > 0)
        {
            end++;
            rest--;
        }
        if(id == 0)
        {
           
           findAllOccurences(start, end, fd);
           exit(0);
        }
        
        
      }
    
    
    
    close(fd[1]);
    
    int index = 0 ;
    int bytes ; 
    //read will wait untill  something is written in the pipe or there is any active writer(not all processes closed fd[1])
    do
    {
       bytes = read(fd[0] ,&result[index] , sizeof(int) * arraySize);
       index += bytes / sizeof(int);
    }while(bytes > 0);
   
   
   
    for(int i = 0 ; i < processesNumber ; i++)
    {
        wait(NULL);
    }
   
    for(int i = 0 ; i < index ; i++)
    {
        printf("%d\n" , result[i]);
    }
   
    
    return 0;
}


