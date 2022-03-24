char* getcommand(char* line);
char* getfilename(char* line);

void main() {
  char line[80];
  char* filename;
  char* command;
  char buffer[13312];
  char ch[1];
  while(1){
    interrupt(0x21, 0, "Shell>\r\n\0", 0, 0);
    interrupt(0x21, 0x01, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    //get the command
    command = getcommand(line, command);
    printString("command is: \0");
    printString(command);
    printString("\r\n\0");

    //get the file name
    filename = getfilename(line, filename);
    printString("filename is: \0");
    printString(filename);
    printString("\r\n\0");
    
    //interrupt to read file
    interrupt(0x21, 0x03, filename, buffer, 0); 
    //interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
  }
}

char* getcommand(char* line, char* command) {
  int i;
  
  while (line[i] != ' ') { //try to get the command name before the space
    command[i] = line[i];
    i++;
  }
  command[i] = '\0';
  return command;
}

char* getfilename(char* line,  char* filename) {
  int i=0;
  int j=0;
  
  while (line[i] != ' ') { //try to reach the space then read the file name 
    i++;
  }
  
  while (line[i] != '\0') { //read the file name from the characters after the space
    filename[j] = line[i];
    j++;
    i++;
  }
  
  filename[j] = '\0';
  return filename;
}
