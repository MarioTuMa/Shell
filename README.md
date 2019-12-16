#Shell:

char ** parse_args( char * line, int commandCount );
  - Separates a string into an array of smaller strings on spaces that can then be used with execvp.

void launch_process(char ** args);
  - Creates a child process by forking to run commands with execvp. It also handels redirection.

char *** sep_colon(char * line, int commandCount);
  - Separates a string into an array of smaller strings on semicolons for the purpose of running multiple commands at once with execvp.

int countChar(char * line,char b);
  - Counts the number of occurances of a given character in a string.

int checkDefaults(char ** args);
  - Checks to see if the command is a default command (cd or exit), and if so executes that command and returns 0 to indicate to not execvp anything sle

##Features:

  Deals with extra spaces. I.e. you can run `ls                ;ls;   ls   ;ls`

##Bugs:

    When running a testfile with ./program < testcoms, the program will at a seemingly random but consistent time, print the prompts all at once and the output intersects with the output of the functions called. This tends to happen near piping commands so there may be a problem there.