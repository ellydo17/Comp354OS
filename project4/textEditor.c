#include "userlib.h"

void main(){
  char* filename;
  char fileBuffer[13312];
  int fileBufferCursor;
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
  printString("Please enter the content you want to write to this file. To quit writing, please enter Ctrl-D and hit return (enter button). \r\n\0");

  fileBufferCursor = 0;
  printString("initial value of fileBufferCursor is: \0");
  printInt(fileBufferCursor);
  printString(".\r\n\0");

  while (fileBufferCursor < 13312) {
    ch = readChar();
    if (ch == 0x04){
      printString("User hit Ctrl-D and return.\r\n\0");
      break;
    }
    fileBuffer[fileBufferCursor] = ch;
    fileBufferCursor++;
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
