#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define Questions 5

//try another approach since pthread_cancel is not a good ideea

void* timeFunc(void* argv)
{
   pthread_t* quiz = (pthread_t*)argv;
   int time = 5;
   while(time > 0)
   {
   	sleep(1);
   	time -= 1;
   	printf("The remaining time is %d\n" , time);
   }
   pthread_cancel(*quiz);
}

void* quizFunc(void* argv)
{
   pthread_t* quiz = (pthread_t*)argv;
   char answer[256];
   pthread_t time;
   pthread_create(&time , NULL , timeFunc , (void*)quiz);
   for(int i = 0 ; i < Questions ; i++)
   {
   	printf("Question %d \n" , i);
   	fgets(answer , sizeof(answer) , stdin);
   }
   pthread_cancel(time);
}



int main(int argc , char* argv[])
{
    char play = 'Y';
    while(play == 'Y')
    {
    	pthread_t quiz;
    
    	pthread_create(&quiz , NULL , quizFunc , (void*)&quiz);
    
    
    	pthread_join(quiz , NULL);
    	printf("Do you want to play again?\n");
    	scanf(" %c" , &play);
    }    

    return 0;
}
