#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char **argv){
  if(argc < 2){
    printf("Please specify a directory \n");
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    directString[strlen(directString)-1]=0;
    opendir(directString);
    if(errno==0){
      printfiles(directString,0);
    }
    else{
      printf("%s\n",strerror(errno));
    }
  }
  else{
      opendir(argv[1]);
      if(errno==0){
        printfiles(argv[1],0);
      }
      else{
        printf("%s\n",strerror(errno));
      }
  }
  return 0;
}
