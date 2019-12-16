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
    getcwd(cwd, 4096);
    printf("%s>", cwd);
    fflush(stdout);
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    if(directString[strlen(directString)-1]=='\n'){
      directString[strlen(directString)-1]='\0';
    }

    int commandCount = countChar(directString,';')+1;
    char*** callParams=sep_colon(directString,commandCount);
    int i;
    for(i=0;i<commandCount;i++){

      launch_process(callParams[i]);
      //free(callParams[i]);
    }
    //free(callParams[commandCount]);
    //free(callParams);
  }
  return 0;
}
