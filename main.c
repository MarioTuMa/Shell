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
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    directString[strlen(directString)-1]='\0';
    int commandCount = countSemis(directString)+1;
    char*** callParams=sep_colon(directString);


    char cd[3] = "cd\n";
    cd[2]-=10;
    int i;
    //printf("%d\n",commandCount);
    for(i=0;i<commandCount;i++){
      if(!strcmp(callParams[i][0],cd)){
        char *dir = strcat(strcat(cwd,"/"),callParams[i][1]);

        if(chdir(dir)){
          printf("%s\n",strerror(errno));
        }
      }
      else{
        launch_process(callParams[i]);
      }
    }

  }
  return 0;
}
