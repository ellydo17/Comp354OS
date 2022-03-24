void main() {
  char line[80];
  char filename[6];
  char* command;
  char buffer[13312];
  char ch[1];
  while(1){
    interrupt(0x21, 0, "Shell>\r\n\0", 0, 0);
    interrupt(0x21, 0x01, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    //get the command
    command = getcommand(line);

    //get the file name
    filename = getfilename(line);
    
    //interrupt to read file
    interrupt(0x21, 0x03, filename, buffer, 0); 
    //interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
  }
}

char* getcommand(char* line) {
  int i;
  char* nameOfCommand;
  
  while (line[i] != ' ') { //try to get the command name before the space
    nameOfCommand[i] = line[i];
    i++;
  }
  return nameOfCommand;
}

char* getfilename(char* line) {
  int i=0;
  int j=0;
  char* nameOfFile;
  
  while (line[i] != ' ') { //try to reach the space then read the file name 
    i++;
  }
  
  while (line[i] != '\0') { //read the file name from the characters after the space
    nameOfFile[j] = line[i];
  }
  
  return nameOfFile;
}
