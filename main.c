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



int main(int argc, char **argv){
  while(1){
    printf("Enter Your Command: ");
    char directString[4096];
    int limit=4096;
    fgets(directString, limit, stdin);
    char **args = parse_args(directString);
    launch_process(args);
    // pid_t child_pid, wpid;
    // int status = 0;

//Father code (before child processes start)

    // for (int id=0; id<1; id++) {
    //   if ((child_pid = fork()) == 0) {
    //     execvp(args[0],args);
    //     free(args);
    //     directString[strlen(directString)-1]=0;
    //     exit(0);
    //   }
    // }
    //
    // while ((wpid = wait(&status)) > 0);
  }
  return 0;
}
