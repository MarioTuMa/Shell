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
    printf("Enter Your Command: ");
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    directString[strlen(directString)-1]='\0';
    //printf("%s\n",directString);
    char** callParams=parse_args(directString);
    //printf("made it here \n");
    //printf("%s\n", (callParams[0]));

    launch_process(callParams);
  }
  return 0;
}
