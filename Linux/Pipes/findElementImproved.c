#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<sys/types.h>
#include <math.h>
#define CPU 4


 int array[17] = {1 , 2 , 3 , 4 , 5 ,6 , 7 , 8 ,9 , 10 ,11 ,12 , 13 , 14 , 15 , 16 , 17};
int findElement(int start , int end , int value)
{
	for(int i = start ; i < end ; i++)
	{
	    if(array[i] == value)
	    {
	     	exit(1);
	    }
	}
	exit(0);
}
int main()
{

    
    int start = 0;
    int size = sizeof(array) / 4;
    int elementsPerProcess = size / CPU;
    int elementToBeFound;
    printf("What element do you want to find?\n");
    scanf("%d" , &elementToBeFound);
    
    
    for(int i = 0 ; i < CPU ; i++)
    {
        pid_t id = fork();
        if(id == 0)
        {
           int start = i * elementsPerProcess;
           int end = start + elementsPerProcess;
           if(i == CPU - 1)
           	end+= size % CPU;
           findElement(start , end , elementToBeFound);
           
        }
    }
    
    
    for(int i = 0 ; i < CPU ; i++)
    {
    	int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus))
        {
           int statusCode = WEXITSTATUS(wstatus);
           //printf("Status code is: %d\n" , statusCode);
           if(statusCode == 1)
           {
              printf("Element found \n");
              exit(0);
           }
        }
    }
    printf("Element not found\n");
    
    return 0;
}
