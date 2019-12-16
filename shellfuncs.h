char ** parse_args( char * line, int commandCount );
void launch_process(char ** args);
char *** sep_colon(char * line, int commandCount);
int countChar(char * line,char b);
int checkDefaults(char ** args);