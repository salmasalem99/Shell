#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<signal.h>
#define MAX_ARG_WORD 10
#define MAX_CHAR 100

int tokenise(char line[], char* arg[])
{
    char* token; int i=1;
    token=strtok(line," ");
    arg[0]=token;
    while(token!=NULL)
    {
        token=strtok(NULL," ");
        arg[i]=token;
        i++;
    }
    return i-1;
}
void append_to_log()
{
    FILE* f = fopen("logfile.txt","a+");
    fprintf(f,"Child process was terminated\n");
    fclose(f);
}
int main()
{
    char* check;
    char* arg[MAX_ARG_WORD];
    char line[MAX_CHAR];
    signal (SIGCHLD, append_to_log);
    while (1) {

        printf(">");
        check = fgets(line,MAX_CHAR,stdin);
        printf("\n");
        line[strlen(line)-1] = 0;

        if (strcasecmp(line,"exit")==0 || check==NULL) 
            exit(0);
        int n=tokenise(line,arg);
        int wait_flag=1;
        if (strcasecmp(arg[n-1],"&")==0) {
            wait_flag=0;
            arg[n-1]=NULL;
        } else {
            arg[n]=NULL;
        }

      int child_pid= fork();
      if(child_pid==0){
        if(execvp(arg[0],arg)<0)
            printf("Command Not Found\n");
	    exit(0);
	    continue;
      }
      else if(wait_flag){
         wait(NULL);
      }
      printf("\n");
    }
    return 0;
}
