#include "userlib.h"

typedef char byte;

struct dirEntry{
  char name[6];
  byte sectors[26];
};

struct directory{
  struct dirEntry entries[16];
};

void main(){
  char* filename;
  int filefound;
  struct directory diskDir;

  enableInterrupts();

  //get the file name from the user
  printString("Enter the name of the file you are looking for: \0");
  readString(filename, 6);
  printString("\r\n\0");

  //read the file from disk sector
  readSector(&diskDir, 2);
  filefound = findFile(filename, &diskDir);

  if (filefound != -1){
    printString("Yay! We found the file you are looking for.\r\n\0");
  }else{
    printString("Sorry! The file you are looking for doesn't exist.\r\n\0");
  }
  
  terminate();
}
