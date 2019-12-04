#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

char ** parse_args(char *line){
  char **args = malloc(4096 * sizeof(char *));
  char *curr = line;
  int i = 0;
  while (*curr != '\0'){

    args[i++] = strsep(&curr, " \n");
    printf("%s\n",args[i-1]);
  }
  args[i] = NULL;
  return args;
}

void launch_process(char ** args){
  pid_t pID, wID;
  int status;

  pID = fork();
  if (pID == 0){
    execvp(args[0],args);
  }
  else{
    wID = waitpid(pID,&status, WUNTRACED);
    while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}
