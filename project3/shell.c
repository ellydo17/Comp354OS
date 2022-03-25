#include "userlib.h"

char* getcommand(char* line);
char* getfilename(char* line);
int compareCommand(char* cmd1, char* cmd2);

void main() {
  char line[80];
  char* filename = "";
  char* command = "";
  int filenameIndex = 0;
  
  char* execute = "execute\0";
  char* type = "type\0";
  
  char buffer[13312];
  int i; //for resetting the buffer
  char ch[1];
  
  while(1){
    
    interrupt(0x21, 0, "Shell> \0", 0, 0);
    interrupt(0x21, 0x01, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
    //printString("Shell>\0");

    /*
    interrupt(0x21, 0, "line is: \0", 0, 0);
    interrupt(0x21, 0, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    */

    //get the command
    /*
    command = getcommand(line);

    interrupt(0x21, 0, "command is:\0", 0, 0);
    interrupt(0x21, 0, command, 0, 0);
    interrupt(0x21, 0, "hmm\0", 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    interrupt(0x21, 0, "line after getting the command name is: \0", 0, 0);
    interrupt(0x21, 0, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    
    //get the file name
    filename = getfilename(line);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    
    interrupt(0x21, 0, "filename is:\0", 0, 0);
    interrupt(0x21, 0, filename, 0, 0);
    interrupt(0x21, 0, "hmm\0", 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    interrupt(0x21, 0, "line after getting the file name is: \0", 0, 0);
    interrupt(0x21, 0, line, 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);

    interrupt(0x21, 0, "command after getting the file name is:\0", 0, 0);
    interrupt(0x21, 0, command, 0, 0);
    interrupt(0x21, 0, "hmm\0", 0, 0);
    interrupt(0x21, 0, "\r\n\0", 0, 0);
    

    if (compareCommand(command, execute) == 0){
      interrupt(0x21, 0, "command is execute\r\n\0", 0, 0);
      
      //interrupt to execute file
      interrupt(0x21, 0x04, filename, 0x2000, 0);
      
    } else if(compareCommand(command, type) == 0){
      interrupt(0x21, 0, "command is type\r\n\0", 0, 0);
      
      //interrupt to read file
      interrupt(0x21, 0x03, filename, buffer, 0);
      //print out the file
      interrupt(0x21, 0, buffer, 0, 0);
      //reset the buffer
      for (i=0; i <= 13312; i++) {
	buffer[i] = 0x00;
      }
      
    } else {
      interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
    }
    */
  }
}

char* getcommand(char* line) {
  char* command = "";
  int i;
  
  while (line[i] != ' ') { //try to get the command name before the space
    command[i] = line[i];
    i++;
  }
  command[i] = '\0';
  i++;
  return command;
}

char* getfilename(char* line) {
  int i=0;
  int j=0;
  char* filename = "";

  while (line[i] != ' ') { //try to get the command name before the space
    i++;
  }
  i++; //skip over the space character
  
  while (line[i] != '\0') { //read the file name from the characters after the space
    filename[j] = line[i];
    j++;
    i++;
  }
  
  filename[j] = '\0';
  return filename;
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
