#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "shellfuncs.h"

char ** parse_args(char *line,int commandCount){
  int counter = 0;
  int currentSize = 0;
  char** parsed_args = malloc(sizeof(char *)*commandCount+sizeof(char *));
  while(line){
      //parsed_args=realloc(parsed_args,sizeof(char *)*counter+sizeof(char *));
      parsed_args[counter]=strsep( &line, " ");
      //printf("%s\n",parsed_args[counter]);
      counter++;
  }
  parsed_args[counter] = NULL;
  return parsed_args;
}

void launch_process(char ** args){
  pid_t pid;
  time_t t;
  int status;

  if ((pid = fork()) < 0)
    perror("fork() error");
  else if (pid == 0) {
    execvp(args[0],args);
    exit(1);
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
        if(WEXITSTATUS(status)){
          printf("Invalid command \n");
        }
      }

      else{
          printf("child did not exit successfully\n");
      }
    }
  } while (pid == 0);
  //printf("made it past \n");
}

char *** sep_colon(char * line,int commandCount){
  int counter = 0;
  int i;
  int currentSize = 0;
  char** parsed_coms = malloc(sizeof(char *)*commandCount+sizeof(char *));
  while(line){
      parsed_coms[counter]=strsep( &line, ";");
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
  free(parsed_coms);
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
