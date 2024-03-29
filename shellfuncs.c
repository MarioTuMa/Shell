#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include "shellfuncs.h"

char ** parse_args(char *line,int commandCount){
  int counter = 0;
  int currentSize = 0;
  char** parsed_args = malloc(sizeof(char *)*commandCount+sizeof(char *));
  while(line){
      //parsed_args=realloc(parsed_args,sizeof(char *)*counter+sizeof(char *));
      char* parsed_argstemp = strsep( &line, " ");
      if(strlen(parsed_argstemp)){
        parsed_args[counter]= parsed_argstemp;
        //printf("%s\n",parsed_args[counter]);
        counter++;
      }
  }
  parsed_args[counter] = NULL;
  return parsed_args;
}

int checkDefaults(char ** args){
  //printf("%s\n",args[0]);
  //printf("Checking defs\n");
  char cwd[4096];
  getcwd(cwd, 4096);
  char cd[3] = "cd";
  char nullipy[1] = "\0";
  char exits[5] = "exit\0";
  if(!strcmp(args[0],cd)){
    char *dir = strcat(strcat(cwd,"/"),args[1]);

    if(chdir(dir)){
      printf("%s\n",strerror(errno));
    }
    return 1;
  }
  else if(strstr(args[0],exits)){
    exit(0);
    return 1;
  }
  //printf("hi\n");
  //printf("%s\n",args[0]);
  return 0;
}
void launch_process(char ** args){
  pid_t pid;
  time_t t;
  int status;
  if(!checkDefaults(args)){
    if ((pid = fork()) < 0)
      perror("fork() error");
    else if (pid == 0) {
      int i=0;
      int redirect=0;
      int arrowIndex = 0;
      int oredirect=0;
      int oarrowIndex = 0;
      int exec=1;
      while(args[i]){
        //printf("%s\n",args[i]);
        if(!strcmp(">",args[i])){
          //printf("We need to redirect >\n");
          redirect=1;
          arrowIndex = i;
          args[i]=NULL;
        }
        if(args[i]){
          if(!strcmp("<",args[i])){
            //printf("We need to redirect <\n");
            oredirect=1;
            oarrowIndex = i;
            args[i]=NULL;
          }
        }

        if(args[i]){
          if (!strcmp(args[i], "|")){         //piping
              FILE *p = popen(args[i-1], "r");
              if (p == NULL){
                  printf("cannot open pipe process\n");
              }
              else {
                  char pipedCommands[4096];
                  FILE *p2 = popen(args[i+1], "w"); //open write end of pipe
                  while (fgets( pipedCommands, sizeof(pipedCommands), p) != NULL) {
                      fputs(pipedCommands, p2); //write info to input of next command
                      //printf("%s->%s", args[0], pipedCommands);
                  }
                  pclose(p2);
              }
              pclose(p);
              exec=0;
          }

        }
        i++;

      }

      if(redirect){
        int out = open(args[arrowIndex + 1], O_RDWR|O_CREAT|O_TRUNC, 0755);
        int d = dup(STDOUT_FILENO);

        dup2(out, 1);
        close(out);
        close(d);
      }
      int file;
      if(oredirect){
        //printf("%s\n",args[oarrowIndex+1]);
        int file = open(args[oarrowIndex + 1], O_RDONLY);
        dup2(file, STDIN_FILENO);


      }
      if(exec){
        execvp(args[0],args);

      }
      close(file);
      exit(0);
    }
    else do {
      if ((pid = waitpid(pid, &status, WNOHANG)) == -1)
        perror("wait() error");
      else if (pid == 0) {
        //time(&t);
        //printf("child is still running at %s", ctime(&t));
        //sleep(1);
      }
      else {
        if (WIFEXITED(status)){
          int b;
        }

        else{
            printf("child did not exit successfully\n");
        }
      }
    } while (pid == 0);
  }

  //printf("made it past \n");
}

char *** sep_colon(char * line,int commandCount){
  int counter = 0;
  int i;
  int currentSize = 0;
  char** parsed_coms = malloc(sizeof(char *)*commandCount+sizeof(char *));
  while(line){
      parsed_coms[counter]=strsep( &line, ";");
      //printf("%s\n",parsed_coms[counter] );
      counter++;
  }
  parsed_coms[counter] = NULL;

  //printf("Seperated on ; \n");

  char*** fleabag = malloc(sizeof(char *)*commandCount+sizeof(char *));
  int bounter = 0;

  for (i = 0; i < counter; i++){
    char * s = parsed_coms[i];
    int numWords = countChar(strcat(parsed_coms[i],"\0"),' ')+1;
    //printf("%d\n",numWords);
    fleabag[i] = parse_args(s,numWords);
    bounter++;
  }
  //free(parsed_coms);
  //fleabag[bounter]=NULL;
  //printf("%d\n",bounter);
  return fleabag;
}


int countChar(char * a,char b){
  if(!a){
    return 0;
  }
  int semis=0;
  int i;
  for(i = 0; a[i] != '\0'; i++){
     if (a[i] == b)
     {
          semis++;
     }
  }
  return semis;
}
