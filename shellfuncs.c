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

char ** parse_args(char *line){
  int counter = 0;
  int currentSize = 0;
  char** parsed_args = malloc(0);
  while(line){
      parsed_args=realloc(parsed_args,8*counter+8);
      parsed_args[counter]=strsep( &line, " " );
      printf("%s\n",parsed_args[counter]);
      counter++;
  }
  parsed_args[counter] = NULL;
  return parsed_args;
}

void launch_process(char ** args){
  pid_t pID, wID;
  int status;

  pID = fork();
  printf("%d\n",pID);
  if (pID == 0){
    printf("child\n");


    execvp(args[0],args);
    exit(1);
  }
  //printf("parent\n");

  while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
    //printf("\n");
    wID = waitpid(pID,&status,WUNTRACED);
    printf("WIFEXITED %d, WIFSIGNALED %d\n",WIFEXITED(status),WIFSIGNALED(status));
  }
  printf("made it past \n");
}
