char ** parse_args( char * line ){

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
