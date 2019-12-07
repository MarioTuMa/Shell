#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "shellfuncs.h"

int main(int argc, char **argv){
  while(1){
    char cwd[4096];
    printf("%s>", getcwd(cwd, 4096));
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    directString[strlen(directString)-1]='\0';
    char** callParams=parse_args(directString);
    char cd[2] = "cd";
    //printf("%s\n", callParams[0]);
    //printf("%d\n", strcmp(callParams[0],cd));
    if(!strcmp(callParams[0],cd)){
      //printf("Hi, we don't know how to cd yet\n");
      chdir(callParams[1]);
    }
    else{
      launch_process(callParams);
    }

  }
  return 0;
}
