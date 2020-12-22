#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#define questionsNumber 5


int main()
{
   char play = 'Y';
   while(play == 'Y')
   {
   int id = fork();
   if(id != 0)
   {
      int id2 = fork();
      
      if(id2 == 0)
      {
      
      char answer[256];
      for(int i = 0 ; i < questionsNumber ; i++)
      {
         printf("The question is %d\n" , i);
         fgets(answer , sizeof(answer) ,stdin);
         getchar();
         
      }
      exit(0);
      }
      else
   {
      
     int firstChild = wait(NULL);
     if(firstChild == id)
     {
     	kill(id2 , SIGKILL);
     }
     else
     {
     	kill(id , SIGKILL);
     }
     wait(NULL);
     printf("\nDo you want to play again : (Y/N)");
     scanf(" %c" , &play);
   }
   }
   
   else{
   
     int time = 30;
     while(time > 0)
     {
        sleep(10);
        time -= 10;
        printf("\nThe left time is %i seconds\n",time);
     }
     printf("Your time expired\n");
     exit(0);
   }
   
   }
   
   return 0;
}
