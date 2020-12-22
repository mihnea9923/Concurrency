#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


volatile int whiteUsers = 0 , blackUsers = 0 , whiteWaiting = 0 , blackWaiting = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void* white(void* arg)
{
  
  pthread_mutex_lock(&mutex);
  
  while(blackUsers > 0 || blackWaiting > whiteWaiting)
  {
  
    if(blackUsers == 0)
    	break;   
    whiteWaiting++;
    pthread_cond_wait(&cond2 , &mutex);
    whiteWaiting--; 
    
  }
   
  printf("White user\n");
  
  whiteUsers++;
  pthread_mutex_unlock(&mutex);
  
  sleep(1);
  pthread_mutex_lock(&mutex);
  whiteUsers--;
  if(whiteUsers == 0)
  {
    pthread_cond_broadcast(&cond1);
  }
  pthread_mutex_unlock(&mutex);

}


void* black(void* arg)
{
   pthread_mutex_lock(&mutex);
   
   while(whiteUsers > 0 || whiteWaiting > blackWaiting + 1) 
   {

     if(whiteUsers == 0)
        break;	
     blackWaiting++;
     pthread_cond_wait(&cond1 , &mutex);
     blackWaiting--;

   }
   
   printf("Black user\n");
  
   blackUsers++;

   pthread_mutex_unlock(&mutex);
   sleep(2);
   pthread_mutex_lock(&mutex);
   blackUsers--;
   
   if(blackUsers == 0)
   {
      pthread_cond_broadcast(&cond2);
   }
    pthread_mutex_unlock(&mutex);
   
}

int main()
{
    pthread_t thread[100];
    srand(time(NULL));
    int threadsNumber = 30;
   
    for(int i = 0 ; i < threadsNumber ; i++)
    {
       if(i  % 2 == 0)
       {
          pthread_create(&thread[i] , NULL , black , NULL);
       }
       else
       {
          pthread_create(&thread[i] , NULL , white , NULL);
       }
    }
    
    for(int i = 0 ; i < threadsNumber ; i++)
    {
        pthread_join(thread[i] , NULL);
    }
    
    

    return 0;
}
