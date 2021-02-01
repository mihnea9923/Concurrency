#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 #include <math.h>
 struct eq{
   int a , b , c;
 };
 struct sol{
   int x1 , x2;
  };
int main()
{
   struct eq equations[100];
   struct sol solutions[100];
   
   srand((unsigned int) time(NULL));
   for(int i = 0 ; i < 100 ; i++)
   {
   	
   	equations[i].a = rand() %  20;
   	equations[i].b = rand() %  10;
   	equations[i].c = rand() %  10;
   } 
   int fd[2];
   //cream pipe-ul care trebuie sa primeasca ca parametru un vector de 2 elemente
   pipe(fd);
   //fork returneaza o valoare care in copil este 0 ,iar in parinte este diferita de 0.Astfel faci deosebirea intre cele 2 procese
   int id = fork(); 
   int id2 = fork();
   if(id == 0)
   {
   	
   	for(int i = 0 ; i < 100 ; i++)
   	{
   	     int delta = equations[i].b * equations[i].b - (4 * equations[i].a * equations[i].c);
   	     write(fd[1] , &delta , sizeof(int));
   	     //pentru a scrie in pipe folosim functia write care ia 3 parametrii,capatul de scriere al pipe-ului,valoarea pe care o scriem si numarul de bytes pe care ii scriem
   	     
   	}
   	
   	
   }
   else
   {
   	
   	for(int i = 0 ; i < 100 ; i++)
   	{
   	   int delta;
   	   read(fd[0] , &delta , sizeof(int));
   	   if(delta < 0)
   	   	delta = delta * -1;
   	   solutions[i].x1 = (-equations[i].b + sqrt(delta)) / 2 * equations[i].a;
   	   solutions[i].x2 = (-equations[i].b - sqrt(delta)) / 2 * equations[i].a;
   	   
   	}
   	
   }
   
   
 return 0;
}
