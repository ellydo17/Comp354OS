#include "userlib.h"

void main(){
  char* filename;
  char fileBuffer[13312];
  char line[80];
  int lineIndex = 0;
  int fileBufferCursor;
  int numCharRead;
  char ch;
  int sectors = 1;

  //get the file name from the user
  printString("Enter a filename: \0");
  readString(filename, 6);
  printString("\r\n\0");

  printString("Thank you! Your filename is: \0");
  printString(filename);
  printString("\r\n\0");

  //prompt the user to type in content for the file
  printString("Please enter the content you want to write to this file. To quit writing, please hit enter and move to the next line, then hit Ctrl-D and and enter. \r\n\0");

  fileBufferCursor = 0;
  printString("initial value of fileBufferCursor is: \0");
  //printInt(fileBufferCursor);
  printString(".\r\n\0");

  while (fileBufferCursor < 13312) {
    printString("reading char \0");
    
    numCharRead = readString(line, 80); //read the string typed in by the user line by line
    
    if (fileBuffer[0] == 0x04){
      printString("User hit Ctrl-D and return.\r\n\0");
      break;
    }

    while(fileBufferCursor < numCharRead){
      fileBuffer[fileBufferCursor] = line[lineIndex];
      fileBufferCursor++;
      lineIndex++;
    }

    fileBuffer[fileBufferCursor] = ' '; //adding space after each line to show continuity in the text
    fileBufferCursor++;
    lineIndex = 0; //reset lineIndex for a new line
    
    printString("Current fileBuffer Cursor is: \0");
    printInt(fileBufferCursor);
    printString(".\r\n\0");
  
    if(mod(fileBufferCursor+1, 512) == 0){
      sectors++;
    }
  }

  printString("Current fileBuffer Cursor is: \0");
  printInt(fileBufferCursor);
  printString(" meaning that there are \0");
  printInt(fileBufferCursor+1);
  printString("characters in the file.\r\n\0");
  
  while (fileBufferCursor < 13312){  
    fileBuffer[fileBufferCursor] = '\0';
    fileBufferCursor++;
  } 

  printString("Remaining space in buffer is filled with null characters.\r\n\0");
  printString("The content stored in buffer is: \0");
  printString(fileBuffer);
  printString(".\r\n\0");
  
  writeFile(filename, fileBuffer, sectors);
  printString("Wrote the file to disk.\r\n\0");
  
  terminate();
}
