#include "stdio.h"
#include <string.h>
#include<unistd.h>
void main(int argc,char *argv[])
{
   FILE *fp1;
   char birkelime[10][250];
   char *string[250][250];
   int c=0;
   int j=0;
	int i=0;
  int k=0;
  int q=0;int qq=0;
  int e=0;int ee=0;

   fp1 = fopen(argv[1],"r");
   int input=0;
   //printf("%s anne",argv[2]);
   if(strcmp(argv[2],"1")==0)
        input=1;
    else if(strcmp(argv[2],"2")==0)
        input = 2;
    else if(strcmp(argv[2],"3")==0)
        input = 3; 
    else if(strcmp(argv[2],"4")==0)
        input = 4;  
    else
        printf("Wrong Argument");
    fp1 = fopen(argv[1],"r");
   do {
      c = fscanf(fp1,"%s",birkelime[i]); /* dosyadan bir kelime oku... */
    if (c != EOF){
     //printf("a:  %s\n",birkelime[i]);
         if (strcmp(birkelime[i],";") == 0)
          e++;
             if(strcmp(birkelime[i],"|") == 0){
                 ee=1;
    }
      if (strcmp(birkelime[i],";") == 0 || strcmp(birkelime[i],"|" )==0 || strcmp(birkelime[i],"\n" )==0){
    string[q][j]=NULL;  
    string[q][j+1]=NULL;  
    j=0;
    q++;
}   
   
else{
string[q][j]=birkelime[i];
//printf("b : %s",string[q][j]);
j++;
}

      i++;
    }
    else{
        string[q][j+1]=NULL;
    }
    
} while (c != EOF);
    int asd=0;
    int as=0;
    if(input == 1){
        int  q =0;
        int qwe=0;
        while(as<e){
            printf("%s ",string[as][0]);
            if(strcmp(string[as][0],"history")==0){
                while(as>qwe){
                    if(string[qwe][q]==NULL){
                        qwe++;
                        q=0;
                    }
                    printf("%s ",string[qwe][q]);
                    q++;
                }
                printf("\n");
            }
            as++;
        }
      while(asd<e){
            pid_t  pid;
            pid = fork();
          if (pid == 0) {
             //printf("PID:%d\n",getpid());
             if(strcmp(string[asd][0],"cd")==0){
                    int ret = chdir(string[asd][1]);
                    if (ret!=0){ // same as ret!=0, means an error occurred and errno is set
                	    printf( "error: %s\n");
                    }
             }
             else{
             execvp(string[asd][0],string[asd]);
             }
             }else if(pid>0){
              int a=0;
              while(string[asd][a]!=NULL){
                 printf("%s ",string[asd][a]);
                 a++;
              }
              printf("\n ");
                wait(NULL);
          }
          asd++;
        }
    }

    else if(input == 2){
        asd=0;
        while(asd<e+1){
            pid_t  pid;
        pid = fork();
         if (pid == 0) {
             //printf("Child:%d\n",getpid());
            execvp(string[asd][0],string[asd]);
         }
         else if(pid>0){
           //printf("Parent:%d\n",getpid());
             int a=0;
            while(string[asd][a]!=NULL){
                 printf("%s ",string[asd][a]);
                 a++;
              }
            wait(NULL);
         }
          else
          {
              printf("fork Failed");
          }
          asd++;
        }
    }
    else if(input == 3){
        while(asd<2*e){
            int a=0;
            while(string[asd][a]!=NULL){
                 printf("%s ",string[asd][a]);
                 a++;
              }
              printf("\n");
              asd++;
     }
    int pipepd[e][2];  
    printf("%d ",e);                 /* dosyayı kapa       */
    for(int i=0;i<2*e;i++) // loop will run n times
    {       
        pipe(pipepd[i]);
        if(fork() == 0 && i<e) //before the "|" declarations
        {
            dup2(pipepd[i][1],STDOUT_FILENO);
            execvp(string[i][0],string[i]);
            perror("execvp");
            exit(0);
        }
       
        
        if(fork() == 0 && i>=e)  //after the "|" declarations
        {
            close(pipepd[i-e][1]);
            dup2(pipepd[i-e][0],STDIN_FILENO);
            execvp(string[i][0],string[i]);
            exit(0);
        }
       
    }
     
    for(int i=0;i<2*e;i++){ // loop will run n times for all children
    wait(NULL);
    close(pipepd[e-i][1]);
    close(pipepd[e-i][0]);
    }
    }
    else if(input == 4){
        if(ee == 1){
             while(asd<2*e){
            int a=0;
            while(string[asd][a]!=NULL){
                 printf("%s ",string[asd][a]);
                 a++;
              }
              printf("\n");
              asd++;
     }
            int pipepd[e][2];  
    printf("%d",e);                 /* dosyayı kapa       */
    for(int i=0;i<2*e;i++) // loop will run n times
    {
        /*printf("first : %s\n",string[i][0]);
        printf("second : %s\n",string[i][1]);*/
        pipe(pipepd[i]);
        if(fork() == 0 && i<e) //before the "|" declarations
        {
            dup2(pipepd[i][1],STDOUT_FILENO);
            execvp(string[i][0],string[i]);
            perror("execvp");
            exit(0);
        }
       
        
        if(fork() == 0 && i>=e)  //after the "|" declarations
        {
            close(pipepd[i-e][1]);
            dup2(pipepd[i-e][0],STDIN_FILENO);
            execvp(string[i][0],string[i]);
            exit(0);
        }
        
    }
     
    for(int i=0;i<2*e;i++){ // loop will run n times for all children
    wait(NULL);
    close(pipepd[e-i][1]);
    close(pipepd[e-i][0]);
    }
        }

        else{
         
        int  q =0;
        int qwe=0;
        while(as<e){
            if(strcmp(string[as][0],"history")==0){
                while(as>qwe){
                    if(string[qwe][q]==NULL){
                        qwe++;
                        q=0;
                    }
                    printf("%s ",string[qwe][q]);
                    q++;
                }
                printf("\n");
            }
            as++;
        }
        asd=0;
      while(asd<e){
            pid_t  pid;
            pid = fork();
          if (pid == 0) {
             //printf("PID:%d\n",getpid());
             if(strcmp(string[asd][0],"cd")==0){
                    int ret = chdir(string[asd][1]);
                    if (ret!=0){ // same as ret!=0, means an error occurred and errno is set
                	    printf( "error: %s\n");
                    }
             }
             else{
                 //printf("%s ",string[0][0]);
             execvp(string[asd][0],string[asd]);
             }
             }else if(pid>0){
              int a=0;
              while(string[asd][a]!=NULL){
                 printf("%s ",string[asd][a]);
                 a++;
              }
                wait(NULL);
          }
          asd++;
        }
        }
    }
    else
        printf("We have a problem");
   fclose(fp1);                    /* dosyayı kapa       */
  
}

