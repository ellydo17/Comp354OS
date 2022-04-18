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
  printString("Please enter the content you want to write to this file. To quit typing, please hit enter and move to the next line, then hit Ctrl-D and press enter. \r\n\0");

  fileBufferCursor = 0;

  while (fileBufferCursor < 13312) {

    //read the string typed in by the user line by line
    numCharRead = readString(line, 80); 
    
    if (line[0] == 0x04){
      break;
    }

    while(numCharRead>0){
      fileBuffer[fileBufferCursor] = line[lineIndex];
      fileBufferCursor++;
      lineIndex++;
      numCharRead--;
    }

    fileBuffer[fileBufferCursor] = ' '; //adding space after each line to show continuity in the text
    fileBufferCursor++;
    lineIndex = 0; //reset lineIndex for a new line
  
    if(mod(fileBufferCursor+1, 512) == 0){
      sectors++;
    }
  }

  //set the value of remaining characters as null
  while (fileBufferCursor < 13312){  
    fileBuffer[fileBufferCursor] = '\0';
    fileBufferCursor++;
  } 

  /*
  printString("The content stored in buffer is: \0");
  printString(fileBuffer);
  printString(".\r\n\0");
  */
  
  writeFile(filename, fileBuffer, sectors);
  
  terminate();
}
