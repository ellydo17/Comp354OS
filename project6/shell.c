#include "userlib.h"

char* getcommand(char* line);
char* getfilename(char* line);
int compareCommand(char* cmd1, char* cmd2);

typedef char byte;

struct dirEntry{
  char name[6];
  byte sectors[26];
};

struct directory{
  struct dirEntry entries[16];
};

void main() {
  char command[30];
  char buffer[13312]; //buffer stores the contents from the file when file is read/program is executed
  int flag = 0; //true if file/program is found and can be executed
  char filename[6];
  
  enableInterrupts();

  printString("OS: Main Menu\r\n\0");
  printString("-------------\r\n\0");
  printString("\r\n\0");
  printString("This is the OS main menu interface, where you can select which function you want the OS to perform. You have the following options:\r\n\0");
  printString("\r\n\0");
  
  while(1){
    printString("1. Read a file\r\n\0");
    printString("2. Execute a program\r\n\0");
    printString("3. Delete a file\r\n\0");
    printString("4. Copy a file\r\n\0");
    printString("5. View all files in directory\r\n\0");
    printString("6. View all processes running currently\r\n\0");
    printString("7. Kill a process\r\n\0");
    printString("8. Find a file\r\n\0");
    printString("\r\n\0");
    printString("Please choose one: \0");

    //get the command
    readString(command, 2);
    if(command[0] == '1' && command[1] == '\0'){
      printString("\r\n\0");
      printString("Type the name of file you want to read: \0");

      readString(filename, 6);
      printString("\r\n\0");
      
      flag = readfile(filename, buffer);

      if (flag != -1) { //file was found
	printString(buffer);
	printString("\r\n\0");
      } else { //file not found, display error
	printString("Error: file not found\r\n\0");
      }
      clearBuffer(buffer);
    }
    
      //command is "execute"
    else if (command[0] == '2' && command[1] == '\0') {
      printString("\r\n\0");
      printString("Type the name of program you want to execute: \0");

      readString(filename, 6);
      printString("\r\n\0");

      flag = executeProgram(filename);

      if (flag == -1) { //file was found
	printString("Error: cannot execute file.\r\n\0");
      } else if (flag == -2) {
	printString("Invalid segment.\r\n\0");
      } else {
	printString("Program was executed.\r\n\0");
      }
    }
    
      //command is "delete"
    else if (command[0] == '3' && command[1] == '\0') {
      printString("\r\n\0");
      printString("Type the name of file you want to delete: \0");

      readString(filename, 6);
      printString("\r\n\0");

      flag = deleteFile(filename);

      if (flag == -1) { //file was found
	printString("Error: cannot delete file because file not found.\r\n\0");
      } else {//file was found
	printString("Successfully deleted file.\r\n\0");
      }
    }

    //command is "copy"
    else if (command[0] == '4' && command[1] == '\0') {
      int iCommand;
      int iSrc;
      int iDest;
      char src[6];
      char dest[6];
      int sectorsRead;
      int sectorsWritten;
      int j=0;
      char buffer2[13312];//will delete later, testing
      
      //printString("Command is copy.\r\n\0");

      //get the name of the source file
      printString("\r\n\0");
      printString("Type the name of the source file that you want to copy: \0");
      
      readString(src, 6);
      printString("\r\n\0");

      //read the source file
      sectorsRead = readfile(src, buffer);

      //if statements to recognize if file read was successful or not
      if (sectorsRead == -1) {
	printString("File not found.\0");
      } else { //write the source file into the destination file
        printString("\r\n\0");
        printString("Type the name of the destination file that you want to copy to: \0");
      
        readString(dest, 6);
        printString("\r\n\0");

	//write to the destination file
	sectorsWritten = writeFile(dest, buffer, sectorsRead);

	//check if write file was possible
	if (sectorsWritten == -1) {
	  printString("Disk directory is full.\r\n\0");
	} else if (sectorsWritten == -2) {
	  printString("Disk is full.\r\n\0");
	}
	
	//printString("Successfully copied source file to destination.\r\n\0");
	clearBuffer(buffer);
      }
    } else if (command[0] == '5' && command[1] == '\0') {
      int iDir = 0;
      struct directory diskDir;
      char* buffer3;
      
      readSector(&diskDir, 2);

      while(iDir < 16) {
	if (diskDir.entries[iDir].name[0] != 0x00) {
	  buffer3 = diskDir.entries[iDir].name;
	  buffer3[6] = '\0';
	  printString(buffer3);
	  printString("\r\n\0");
	}
	iDir++;
      }
      clearBuffer(buffer3);

     //command is "ps"
    } else if (command[0] == '6' && command[1] == '\0') {
      //printString("Command is ps.\r\n\0");

      showProcesses();

      printString("ps is finished.\r\n\0");

      //command is "kill"
    } else if (command[0] == 'k' && command[1] == 'i' && command[2] == 'l' && command[3] == 'l' && command[4] == ' ') {
      int segIndex;
      char seg = command[5];
      
      printString("Command is kill.\r\n\0");

      
      printString("Segment to kill is \0");

      if (seg == '0') {
	segIndex = 0;
	printString("0\0");
      } else if (seg == '1') {
	segIndex = 1;
	printString("1\0");
      } else if (seg == '2') {
	segIndex = 2;
	printString("2\0");
      } else if (seg == '3') {
	segIndex = 3;
	printString("3\0");
      } else if (seg == '4') {
	segIndex = 4;
	printString("4\0");
      } else if (seg == '5') {
	segIndex = 5;
	printString("5\0");
      } else if (seg == '6') {
	segIndex = 6;
	printString("6\0");
      } else if (seg == '7') {
	segIndex = 7;
	printString("7\0");
      } else {
	segIndex = -1;
	printString("-1\0");
      }

      printString(".\r\n\0");

      if (segIndex != -1) {	
	flag = kill(seg);

	printString("Value of flag is \0");
	if (flag == 1) {
	  printString("1\r\n\0");
	} else {
	  printString("-1\r\n\0");
        }

	if (flag == 1) { //the process was killed
	  printString("Shell: The process was successfully killed.\r\n\0");
	} else { //no process was running in the segment with the specified index
	  printString("Shell: There is no process currently running in the segment with the specified index.\r\n\0");
	}
      } else {
	printString("invalid segment index\r\n\0");
      }
      
      printString("kill is finished.\r\n\0");

      //command is find
    } else if (command[0] == '8' && command[1] == '\0') {
      char fileIndex[2];
      struct directory diskDir;
      
      fileIndex[1] = '\0';
      //printString("Command is find.\r\n\0");

      //get the name of the file that we want to find
      printString("\r\n\0");
      printString("Type the name of the file that you want to find: \0");
      
      readString(filename, 6);
      printString("\r\n\0");

      printString("The name of the file is: \0");
      printString(filename);
      printString("\r\n\0");

      //read the file from disk sector
      readSector(&diskDir, 2);
      flag = findFile(filename, &diskDir);
      fileIndex[0] = flag;

      if (flag != -1) { //file was found
	printString("File was found at index\0");
	printString(fileIndex);
	printString(".\r\n\0");
      } else { //file not found, display error
	printString("Error: cannot find the file.\r\n\0");
      }
      clearBuffer(fileIndex);
      
    //command is invalid 
    } else {
      printString("Unrecognized command.\r\n\0");
    }  
    
  }
}
