#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#define CPU 4


int main()
{
    int array[16] = {1 , 2 , 3 , 4 , 5 ,6 , 7 , 8 ,9 , 10 ,11 ,12 , 13 , 14 , 15 , 16};
    int forks[100];
    int start = 0;
    int size = sizeof(array) / 4;
    int processesNumber = pow(2 , CPU);
    int sum = 0;
    int parentChild[2] , childParent[2];
    if(pipe(parentChild) == -1)
    {
        return -2;
    }
    if(pipe(childParent) == -1)
    {
        return -1;
    }
    
    
    for(int i = 0 ; i < CPU ; i++)
    {
        forks[i] = fork();
        if(forks[i] == 0)
        {
             childWork(i , array , size);
    	     exit(0);
        }
    }
   
       
    int isRoot = 1;
    for(int j = 0 ; j < CPU ; j++)
     {
        if(forks[j] == 0)
            isRoot = 0;
     }
    if(isRoot == 1)
    {
        close(parentChild[0]);
        for(int i = 0 ; i < processesNumber - 1 ; i++)
        {
            start += size  / processesNumber;
            
            if(write(parentChild[1] , &start , sizeof(int)) == -1)
                return 1;
        }            
        start = 0;
        close(parentChild[1]);
    }
    else
    {	close(parentChild[1]);
        if(read(parentChild[0] , &start , sizeof(int)) == -1)
            return 2;
        close(parentChild[0]);    
    }
    for(int i = start ; i < start + size / processesNumber ; i++)
    {
        sum += array[i];
    }
    printf("Sum is %d\n" , sum);
    if(isRoot == 0)
    {
        close(childParent[0]);
        if(write(childParent[1] , &sum , sizeof(int)) == -1)
            return 3;
        exit(0);    
    }
    else
    {
        close(childParent[1]);
        int childSum;    
        for(int i = 0 ; i < processesNumber -1 ; i++)
        {
            if(read(childParent[0] , &childSum , sizeof(int)) == -1)
                return 4;
            sum += childSum;
            
        }
        close(childParent[0]);
        printf("The sum is: %d\n" , sum);
    }
    for(int i = 0 ; i < processesNumber ; i++)
    {
    	wait(NULL);
    }
    
    return 0;
}
