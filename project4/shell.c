#include "userlib.h"

char* getcommand(char* line);
char* getfilename(char* line);
int compareCommand(char* cmd1, char* cmd2);

void main() {
  char command[80];
  char buffer[13312]; //buffer stores the contents from the file when file is read/program is executed
  int flag = 0; //true if file/program is found and can be executed

  int iCommand;
  int iSrc;
  int iDest;
  char* src;
  char* dest;
  int sectorsRead;
  int sectorsWritten;
  
  while(1){
    //Print out shell command as "Shell> "
    printString("Shell> \0");

    //get the command
    readString(command);
    printString("\r\n\0");

    //compare command and execute it accordingly
    
    //command is "type"
    if (command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e' && command[4] == ' ') {
      //printString("Command is type.\r\n\0");
      
      flag = readfile(command+5, buffer);

      if (flag != -1) { //file was found
	printString(buffer);
      } else { //file not found, display error
	printString("Error: file not found\r\n\0");
      }
    }
    
      //command is "execute"
    else if (command[0] == 'e' && command[1] == 'x'&& command[2] == 'e' && command[3] == 'c' && command[4] == 'u' && command[5] == 't' && command[6] == 'e' && command[7] == ' ') {
      //printString("Command is execute.\r\n\0");

      flag = executeProgram(command+8, 0x2000);

      if (flag == -1) { //file was found
	printString("Error: cannot execute file.\r\n\0");
      } else if (flag == -2) {
	printString("Invalid segment.\r\n\0");
      } else {
	printString("Program was executed.\r\n\0");
      }

      //command is invalid 
    }
    
      //command is "delete"
    else if (command[0] == 'd' && command[1] == 'e'&& command[2] == 'l' && command[3] == 'e' && command[4] == 't' && command[5] == 'e' && command[6] == ' ') {
      printString("Command is delete.\r\n\0");

      flag = deleteFile(command+7);

      if (flag == -1) { //file was found
	printString("Error: cannot delete file because file not found.\r\n\0");
      } else {//file was found
	printString("Successfully deleted file.\r\n\0");
      }

      //have to add write file here
      
      //command is invalid 
    }

    //command is "copy"
    else if (command[0] == 'c' && command[1] == 'o'&& command[2] == 'p' && command[3] == 'y' && command[4] == ' ') {
      printString("Command is copy.\r\n\0");

      //from index 5, iterate through the remaining characters until we find a space, say we found space at index n, src = command+5 to command+(n-1), dest = command+n+1
      //read file (src)
      //write file (dest)
      iCommand = 5;
      iSrc = 0;
      iDest = 0;
      
      while(command[iCommand] != ' ') {
	src[iSrc] = command[iCommand];
	iSrc++;
	iCommand++;
      }
      src[iSrc]=0x00;
      iCommand++;

      while(command[iCommand] != 0x00) {
	dest[iDest] = command[iCommand];
	iDest++;
	iCommand++;
      }
      dest[iDest]=0x00;

      printString("src is \0");
      printString(src);
      printString(".\r\n\0");
      printString("dest is \0");
      printString(dest);
      printString(".\r\n\0");

      //read the source file
      sectorsRead = readfile(src, buffer);
      printString("sectors read is \r\n\0");
      
      //if statements to recognize if file read was successful or not
      if (sectorsRead == -1) {
	printString("File not found.\0");
      } else { //write the source file into the destination file
	printString("source file was found.");
	sectorsWritten = writeFile(dest, buffer, sectorsRead);

	printString("sectors written is \r\n\0");
	
	if (sectorsWritten == -1) {
	  printString("Disk directory is full.\r\n\0");
	} else if (sectorsWritten == -2) {
	  printString("Disk is full.\r\n\0");
	}
	
	printString("Successfully copied source file to destination.\r\n\0");
      }
      //command is invalid 
    }else { 
      printString("Unrecognized command.\r\n\0");
    }
    
  }
}
