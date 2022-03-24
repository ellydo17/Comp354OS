char* getcommand(char* line);
char* getfilename(char* line);
int compareCommand(char* cmd1, char* cmd2);

void main() {
  char line[80];
  char* filename;
  char* command;
  char* execute = "execute\0";
  char* type = "type\0";
  char buffer[13312];
  char bufferReset[13312]; //to reset the buffer after an interrupt
  char ch[1];
  while(1){
    interrupt(0x21, 0, "Shell> \0", 0, 0);
    interrupt(0x21, 0x01, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    /*
    interrupt(0x21, 0, "line is: \0", 0, 0);
    interrupt(0x21, 0, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    */

    //get the command
    getcommand(line, &command);

    
    interrupt(0x21, 0, "command is:\0", 0, 0);
    interrupt(0x21, 0, command, 0, 0);
    interrupt(0x21, 0, "hmm\0", 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    
    
    //get the file name
    getfilename(line, &filename);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    
    interrupt(0x21, 0, "filename is:\0", 0, 0);
    interrupt(0x21, 0, filename, 0, 0);
    interrupt(0x21, 0, "hmm\0", 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    

    if (compareCommand(&command, &execute) == 0){
      interrupt(0x21, 0, "command is execute\r\n\0", 0, 0);
      
      //interrupt to execute file
      interrupt(0x21, 0x04, filename, 0x2000, 0);
      
    } else if(compareCommand(&command, &type) == 0){
      interrupt(0x21, 0, "command is type\r\n\0", 0, 0);
      
      //interrupt to read file
      interrupt(0x21, 0x03, filename, buffer, 0);
      //print out the file
      interrupt(0x21, 0, buffer, 0, 0);
      //reset the buffer
      //buffer = bufferReset;
      
    } else {
      interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
    }
    
  }
}

int getcommand(char* line, char* command) {
  int i;
  
  while (line[i] != ' ') { //try to get the command name before the space
    command[i] = line[i];
    i++;
  }
  command[i] = '\0';
  return i;
}

int getfilename(char* line,  char* filename) {
  int i=0;
  int j=0;
  
  while (line[i] != ' ') { //try to reach the space then read the file name 
    i++;
  }
  i++; //skip the space character
  
  while (line[i] != '\0') { //read the file name from the characters after the space
    filename[j] = line[i];
    j++;
    i++;
  }
  
  filename[j] = '\0';
  return j;
}

int compareCommand(char* cmd1, char* cmd2) {
  int flag=0; //default true, command is same

  interrupt(0x21, 0, "compareCommand is called.\r\n\0", 0, 0);
  
  interrupt(0x21, 0, "cmd1 is\0", 0, 0);
  interrupt(0x21, 0, cmd1, 0, 0);
  interrupt(0x21, 0, "\r\n\0", 0, 0);

  interrupt(0x21, 0, "cmd2 is\0", 0, 0);
  interrupt(0x21, 0, cmd2, 0, 0);
  interrupt(0x21, 0, "\r\n\0", 0, 0);
  
  interrupt(0x21, 0, "compareCommand is called.\r\n\0", 0, 0);

  while(*cmd1 != '\0' && *cmd2 != '\0'){
    interrupt(0x21, 0, "cmd1 is:\0", 0, 0);
    interrupt(0x21, 0, *cmd1, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    interrupt(0x21, 0, "cmd2 is:\0", 0, 0);
    interrupt(0x21, 0, *cmd2, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    
    if(*cmd1 != *cmd2){ //commands not same
      flag = 1; //false, command not same
      break;
    }
    *cmd1++;
    *cmd2++;
  }
  if(flag == 0){
    return 0; //same
  }else{
    return 1; //not same
  }
}
