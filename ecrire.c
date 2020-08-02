#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uvsqgraphics.h>

int
main ()
{

  
  FILE *f;
  FILE *fd;
  f = fopen ("fich_D.txt", "r");
  fd = fopen ("fich_D_2.txt", "w");
  int d,a,t;
  int i;
  char type[50];
  fscanf(f,"%d %d",&d,&a);
  fprintf(fd,"%d %d\n",d,a);
  for (i = 1; i <=231; i++)
    {
      fscanf(f,"%d %d %d %s",&d,&a,&t,type);
/*if (strcmp(type,"rouge")==0){
		   strcpy(type,"piste_rouge");
             fprintf(fd,"%d %d %d %s\n",d,a,t,type);}
       else{
       if (strcmp(type,"vert")==0){
          strcpy(type,"piste_vert");
		  fprintf(fd,"%d %d %d %s\n",d,a,t,type);}
		  else{
          if (strcmp(type,"bleu")==0){
          strcpy(type,"piste_bleu");
		  fprintf(fd,"%d %d %d %s\n",d,a,t,type);}
		  else{
			if (strcmp(type,"noir")==0){
          strcpy(type,"piste_noir");
		  fprintf(fd,"%d %d %d %s\n",d,a,t,type);}
		  else*/
		  t=t*10;
		  fprintf(fd,"%d %d %d %s\n",d,a,t,type);
	      }
	     
		  
	  
	  
	  
     
    
  fclose (f);
  fclose (fd);
  

  return 0;
}
