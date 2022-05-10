#define MAIN

#include "proc.h"

/*
 * @author Elly Do, Sweta Tamrakar, Amelia Dao
 * @date April 24, 2022
 */



void putStr(int col, int row, char character[], char color);

void putChar(int col, int row, char character, char color);

int printString(char *str);

int readChar();

int readString(char *buf, int maxChar);

int readSector(char *buf, int absSector);

int handleInterrupt21(int ax, int bx, int cx, int dx);

int printInt(int num);

int getNumDigits(int num);

void reverse(char* numStr, int numDigits);

char* itoa(int num);

int readfile(char *filename, char *buf);

int findFile(char *filename, struct directory *diskSector);

typedef char byte;

struct dirEntry{
  char name[6];
  byte sectors[26];
};

struct directory{
  struct dirEntry entries[16];
};

void terminate();

int executeProgram(char *name);

int writeSector(char *buf, int absSector);

int deleteFile(char* filename);

int writeFile(char *filename, char *buffer, int sectors);

void handleTimerInterrupt(int segment, int stackPointer);

void kStrCopy(char *src, char *dest, int len);

void yield();

void showProcesses();

int kill(int segment);

void main() {
  //tests for project 5

  //tests for timer interrupts
  
  initializeProcStructures();
  makeInterrupt21();
  handleInterrupt21(0x04,"shell\0",0x2000,0);
  makeTimerInterrupt();
  
  //tests for project 4

  //tests for "TextEditor"
  /*
  makeInterrupt21();
  interrupt(0x21, 0x04, "textEditor\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  */
  
  //tests for "Writing a file"
  /*
  char buffer[13312];
  writeFile("apple\0", "writing to a file that already exists, if this prints out, it means that the text was successfully written into the file.", 3);
  readfile("apple\0", buffer);
  printString(buffer);
  */

  /*
  char buffer[13312];
  writeFile("testNE\0", "This part is testing if we can write to a file that does not exist. If this prints out, it means that the writefile method works for a file that does not exist.", 3);
  readfile("testNE\0", buffer);
  printString(buffer);
  */
  
  
  //tests for "Deleting a File"
  /*
  //load new file first, will delete it later
  char buffer[13312]; // the maximum size of a file
//  makeInterrupt21();
  //read the file into buffer
 // interrupt(0x21, 0x03, "delete\0", buffer, 0);
  //print out the file
 // interrupt(0x21, 0x00, buffer, 0, 0);
  */
  //delete the file "fileToDelete"
  /*
  interrupt(0x21, 0x07, "happy1\0", 0, 0);
  printString("deleted file\r\n\0");
  */
  
  
  //tests for "Writing a Disk Sector"
  /*
  char* buffer1 = "Today Is Sunday";
  writeSector(buffer1,2789);
  */
  
  //tests for project 3

  //tests for "Command line shell"
  /*
  makeInterrupt21();
  interrupt(0x21, 0x04, "shell\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  */
  
  //tests for "Terminating a User Program"
  /*
  makeInterrupt21();
  interrupt(0x21, 0x04, "uprog2\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  */

  //tests for "Loading and Executing a Program"
  /*
  makeInterrupt21();
  interrupt(0x21, 0x04, "uprog1\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  */

  //tests for "Loading and Printing a File"
  /*
  char buffer[13312]; // the maximum size of a file
  makeInterrupt21();
  //read the file into buffer
  interrupt(0x21, 0x03, "messag\0", buffer, 0);
  //print out the file
  interrupt(0x21, 0x00, buffer, 0, 0);
  */
  
  while(1) {
  /*infinite loop*/
  }
}

/* Functions for project 5 */

/*
 * This function should kill the process that is executing in the segment with the specified index.
 * @segment: The specified index
 */
int kill(int segment){
  int actualSeg;
  int memory;
  struct PCB* PCBToFree;

  setKernelDataSegment();
  printString("kill is in progress\r\n\0");

  memory = memoryMap[segment];
  restoreDataSegment();
  
  if (memory == USED) {
    setKernelDataSegment();
    PCBToFree = &pcbPool[segment+1];
    releasePCB(PCBToFree); //free the PCB
    actualSeg = (segment * 0x1000) + 0x2000;
    releaseMemorySegment(actualSeg); //set the segment to be free
    restoreDataSegment();
    return 1;
  } else {
    printString("There is no process currently running in the segment with the specified index\r\n\0");
    return -1;
  }
}

/*
 * This function should display a list of the names and memory segment indices of all of the currently executing processes.
 */
void showProcesses(){
  struct PCB* curPCB;
  int segIndex;
  int memory;
  int memoryMapIndex; 

  setKernelDataSegment();
  printString("showProssess is running\r\n\0");
  
  for(memoryMapIndex = 0; memoryMapIndex < 8; memoryMapIndex++) {
    memory = memoryMap[memoryMapIndex];
    if (memory == USED) {
      curPCB = &pcbPool[memoryMapIndex+1];
      segIndex = curPCB->segment;
      //segIndex = (curPCB->segment/0x1000) - 2;

      //print out executing process's name and segment index first
      printString("name = \0");
      printString(curPCB->name);
      printString(", segment index = \0");
      //printInt(segIndex);
      if (memoryMapIndex == 0) {
	printString("0\0");
      } else {
        printInt(memoryMapIndex);
      }
      printString("\r\n\0");
    }
  }
  restoreDataSegment();
}

/*
 * This function causes the executing process to give up the remainder of its time slice and be put back into the ready queue.
 */
void yield(){
  interrupt(0x21, 0x0C, 0, 0, 0);
}

/* kStrCopy(char *src, char *dest, int len) copy at most len
 * characters from src which is addressed relative to the current 
 * data segment into dest which is addressed relative to the
 * kernel's data segment (0x1000).
 */
void kStrCopy(char *src, char *dest, int len) {
  int i=0;
  for (i=0; i<len; i++) {
    putInMemory(0x1000, dest+i, src[i]);
    if (src[i] == 0x00) {
      return;
    }
  }
}

/*
 * Timer Interrupts
 * The timer_ISR function will pass the memory segment (e.g. 0x3000 or 0x5000) and 
 * stack pointer of the interrupted process to your handleTimerInterrupt function.
 */

void handleTimerInterrupt(int segment, int stackPointer) {
  struct PCB* removedPCB;
  int newSegment;
  int newStackPointer;

  setKernelDataSegment();
  
  //save the stack pointer into the PCB of the running process
  running->stackPointer = stackPointer;

  if(running->name != idleProc.name){
    addToReady(running);
  }

  //get a new process from the ready queue
  removedPCB = removeFromReady();
  newSegment = removedPCB->segment;
  newStackPointer = removedPCB->stackPointer;

  //mark it as RUNNING
  removedPCB->state = RUNNING;
    
  //set the running variable to point to it
  running = removedPCB;

  restoreDataSegment();
  
  //invoke the returnFromTimer method with the segment and stack pointer of the new running process.
  returnFromTimer(newSegment, newStackPointer);
}

/* Functions for project 4 */

/*
 * Writing a File
 */

int writeFile(char * filename, char * buffer, int sectors){

  char diskMap[512];
  struct directory diskDir;

  int dirEntry, i,j,idx, remaining;
  int sectorCounter = 0;//index for sectors in the entry
  int fileNameLen = 0;

  int sectorIndexDisk; //index for sectors in disk
  int oldSector;//previous sectors used by the file

  char sectorBuffer[512];//buffer for each sector so that it can be easily copied into the assigned sector

  int foundEmptyEntry = -1; //check if there is an empty entry in the diskmap, default is false

  int bufferIndex = 0;;

  if (sectors > 26) {
    sectors = 26;
  }

  //delete the file if file already exists, will rewrite the file as though it never existed. 
  deleteFile(filename);

  //read the diskmap and disk directory
  readSector(diskMap,1);
  readSector(&diskDir,2);
  
  //finding an empty entry in the Disk Directory
  for(dirEntry = 0; dirEntry < 16; dirEntry++){
    if(diskDir.entries[dirEntry].name[0] == 0x00){
      foundEmptyEntry = 1;
      break;
    }
  }

  //if there is no empty entry in the diskmap, return -1
  if(foundEmptyEntry == -1){
    printString("There is no Disk Directory entry available for the new file.\0");
    return -1;
  }

  //get the length of filename
  while(filename[fileNameLen] != '\0' && filename[fileNameLen] != 0x00){
    fileNameLen++;
  }

  //store the filename into the disk directory at the index of the empty entry we found earlier
  for(j = 0; j < fileNameLen; j++){
    diskDir.entries[dirEntry].name[j] = filename[j];
  }

  //if file name is fewer than 6 characters, fill the remaining characters with 0x00
  if(fileNameLen < 6){
    remaining = 6 - fileNameLen;

    for(j = 0; j < remaining; j++){
      diskDir.entries[dirEntry].name[j+fileNameLen] = 0x00; 
    }
  }

  //write the given content into the sectors assigned to the new file
  for(sectorCounter = 0; sectorCounter < sectors; sectorCounter++){
    sectorIndexDisk = 0;

    //find an empty sector in diskMap, the empty sector index = sectorNum
    while(diskMap[sectorIndexDisk] != 0x00){
      sectorIndexDisk++;
    }

    //if there is no available space in the diskMap, return -2
    if(sectorIndexDisk >= 512){
      printString("Disk Map contains fewer sectors than requested!\0");
      return -2;
    }

    //free up old used space
    oldSector = diskDir.entries[dirEntry].sectors[sectorCounter];
    diskMap[oldSector] = 0x00;

    //mark new space as occupied
    diskMap[sectorIndexDisk] = 0xFF;
    //save the new space used for the file in the file's sector structure
    diskDir.entries[dirEntry].sectors[sectorCounter] = sectorIndexDisk;

    //copy parts of the buffer into the sectorBuffer which is a buffer specified for that particular sector
    for(j = 0; j < 512; j++){
      sectorBuffer[j] = buffer[bufferIndex];
      bufferIndex++;
    }

    writeSector(sectorBuffer, sectorIndexDisk);
  }

  writeSector(diskMap,1);
  writeSector(&diskDir,2);

  return sectors;
}

/*
 * Deleting a File
 */
int deleteFile(char* filename){
  int fileIndex = -1;
  int i = 0;
  int sector;
  struct directory diskDir;
  char diskMap[512];
  
  //read the file from disk sector
  readSector(diskMap,1);
  readSector(&diskDir, 2);
  
  //helper method to find the file in disk
  fileIndex = findFile(filename, &diskDir);
  //if file is found, all sectors allocated to the file must be marked as free and thee first char og the filename must also be set to 0x00
  if(fileIndex != -1){ //file found
    
    while(diskDir.entries[fileIndex].sectors[i] != 0x00 && i < 26) {
      sector = diskDir.entries[fileIndex].sectors[i];
      i++;
      //free up space for that particular sector
      diskMap[sector] = 0x00;
    }
    
    //replace first char of filename if file was found
    diskDir.entries[fileIndex].name[0] = 0x00;
    writeSector(diskMap, 1);
    writeSector(&diskDir, 2);
  }else{
    //printString("Error: file doesn't exist.\0");
    return -1;
  }
  return 1;
}

/*
 * Writing a Disk Sector
 */

int writeSector(char *buf, int absSector){
  int relSector;
  int head;
  int track;
  relSector = mod(absSector, 18) + 1;
  head = mod(absSector /18, 2);
  track = ( absSector / 36 );
  interrupt(0x13, 0x03 * 256 + 0x01, buf, track * 256 + relSector, head * 256 + 0x00);
  return 1;
}

/* Functions for project 3 */

/*
 * Terminating a user program
 */

void terminate() {
  //reset the segment registers and stack pointer to the memory segment containing the kernel
  resetSegments();

  //free the memory segment that it is using, free the PCB that it is using
  setKernelDataSegment();
  releaseMemorySegment(running);
  restoreDataSegment();

  setKernelDataSegment();
  releasePCB(running);
  restoreDataSegment();
  //set its state to DEFUNCT
  running->state = DEFUNCT;

  //enter an infinite while loop
  while(1);
}

/*
 * Loading and executing a program
 */

int executeProgram(char *name){
  char buffer[13312];
  int i = 0;
  int totalSectorsRead = readfile(name, buffer);
  int segmentIndex;
  int segment;
  struct PCB *pcBlock;
  int nameIndex=0;
  
  if (totalSectorsRead == -1) { //if program/file not found
    return -1;
  }else{  //if program/file found
    //get the free memory segment (global structure)
    setKernelDataSegment();
    segmentIndex = getFreeMemorySegment();
    restoreDataSegment();
    
    if (segmentIndex == -1) { //couldn't find a free memory segment
      return -2;
    } else { //segment found
      //convert the segment index to actual segment
      segment = 0x2000 + (segmentIndex * 0x1000);
      
      //obtain a PCB for the process, initialize it and add to ready queue
      setKernelDataSegment();
      pcBlock = getFreePCB();
     
      //set the state of process and segment
      pcBlock->state = READY; 
      pcBlock->segment = segment; //segment where the process is loaded
      pcBlock->stackPointer = 0xFF00;

      addToReady(pcBlock);

      restoreDataSegment();
      
      //iterate through the buffer and place each element from the
      //buffer into the memory segment
      while (i < (totalSectorsRead*512)) {
	putInMemory(segment, i, buffer[i]);
	i++;
      }
    }
  }
        
  //set the name of process to the name of file given in the parameter
  kStrCopy(name, pcBlock->name, 7);
 
  //launchProgram(segment);
  initializeProgram(segment);
  printString("completed execute program method\r\n\0");
  return 1;
}

/*
 * Loading and printing file
 */

int readfile(char *filename, char *buf){
  int totalSectorsRead = 0;
  int fileIndex = -1;
  int i = 0;
  int sector;
  int bufIndex = 0;

  struct directory diskDir;
  
  //read the file from disk sector
  readSector(&diskDir, 2);

  //printString("running readFile method.\r\n\0");
  
  //helper method to find the file in disk
  fileIndex = findFile(filename, &diskDir);
  /*
  printString("The file index is \0");
  printInt(fileIndex);
  printString(".\r\n\0");
  */
  
  //read contents from the file if file was found
  if(fileIndex != -1){ //file found
    //check if the sector is empty or if we have reached the end of sectors
    while(diskDir.entries[fileIndex].sectors[i] != 0x00 && i < 26) {
      sector = diskDir.entries[fileIndex].sectors[i];
      i++;

      //put the content from the sector into buf
      readSector(buf+bufIndex, sector);   
      totalSectorsRead++;

      //each sector has 512 bytes, so increment bufIndex by 512 bytes once a sector is read
      bufIndex = bufIndex + 512;
      /*
      printString("Buf index is \0");
      printInt(bufIndex);
      printString(".\r\n\0");
      */
    }
  }else{
    printString("Error: file not found\0");
    return -1;
  }

  return totalSectorsRead;
}

/*
 * Helper method for the readfile method
 * It returns the index of the file we are looking for in the disk sector 
 * if it is found, returns -1 otherwise
 */

int findFile(char *filename, struct directory* diskDir){
  int i = 0;
  int j = 0;
  
  for(i=0; i<16; i++){
    for(j=0; j<6; j++){
      if(diskDir->entries[i].name[j] != filename[j]){
	break;
      }
      if(j==5){ //found file
	return i; // index of the file in the disk sector
      }
    }
  }
  
  return -1;
}

/* Functions for project 2 */

/*
 * Bonus 2 feature: printInt function accepts a single integer argument 
 * and prints its decimal value to the screen
 */

int printInt(int num){
  //get the number of digits
  int numDigits = getNumDigits(num);
  
  //convert the integer to string
  char *str = itoa(num);
  
  //print out the string
  printString(str);
   
  //return the numbers of digits printed out
  return numDigits;
}

/*
 * Helper method for printInt function
 * It returns the number of digits that make up the integer value num
 */

int getNumDigits(int num){
  int length = 0;
  if (num < 0) {
    length = 1;
  }
  while (num != 0) {
    length++;
    num = num/10;
  }
  return length;
}

/*
 * Helper method for printInt function
 * It returns the string representation of the integer num
 */

char* itoa(int num){
  int i = 0;
  char* resultStr = "";
  int isNeg = 0; //false
  char readChar[2];
  char* numList = "0 1 2 3 4 5 6 7 8 9\0";

  //set the first character as the null terminator
  resultStr[i] = '\0';
  i++;
    
  if (num == 0){
    resultStr[i] = '0';
    i++;
    return resultStr;
  }
 
  if (num < 0){
    isNeg = 1; //true
    num = -num;
  }
  
  while (num != 0) {
    int rem = mod(num, 10);
    readChar[0] = numList[rem*2];
    resultStr[i] = readChar[0];
    i++;
    num = num/10;
  }
  
  if (isNeg==1){
    resultStr[i] = '-';
    i++;
  }
    
  reverse(resultStr, i);
  return resultStr;
}

/*
 * Helper method for printInt function
 * It returns the reversed version of the string numStr
 */

void reverse(char* numStr, int numDigits) {
  int begin = 0;
  int terminate = numDigits - 1;
  while (begin < terminate) {
    int temp = numStr[begin];
    numStr[begin] = numStr[terminate];
    numStr[terminate] = temp;
    
    begin++;
    terminate--;
  }
}

/*
 * Modify the handleInterrupt21 function to create system calls that allow 
 * us to print a string, read a character, read a string, read a file, and 
 * load and execute a program using the printString, readChar, readString, 
 * readfile, and executeProgram functions
 */

int handleInterrupt21(int ax, int bx, int cx, int dx){
  if (ax == 0x00) { //0x00 specifies that we need to print a string
    return printString(bx);
  }else if (ax == 0x11) { //0x11 specifies that we need to read a character
    char ch = readChar();
    char* buf = bx;
    buf[0] = ch;
    return 1;
  }else if (ax == 0x01) { //0x01 specifies that we need to read a string (read characters until ENTER is pressed)
    return readString(bx, cx);
  }else if (ax == 0x02) { //0x02 specifies that we need to read a sector
    return readSector(bx,cx);
  }else if (ax == 0x03) { //0x03 specifies that we need to read the contents of a file into a buffer (project 3)
    return readfile(bx,cx);
  }else if (ax == 0x04) { //0x04 specifies that we need to load a program into memory annd execute it (project 3)
    return executeProgram(bx);
  } else if (ax == 0x05) {  //0x05 specifies that we need to terminate a user program (project 3)
    return terminate();
  }else if (ax == 0x07) {  //0x05 specifies that we need to terminate a user program (project 3)
    return  deleteFile(bx);
  }else if (ax == 0x08) {  //0x05 specifies that we need to terminate a user program (project 3)
    return  writeFile(bx,cx,dx);
  }else if (ax == 0x09) {  //0x05 specifies that we need to terminate a user program (project 3)
    return  yield();
  }else if (ax == 0x0A) {  //0x0A specifies that we need to display all data of processes (project 5)
    return  showProcesses();
  }else if (ax == 0x0B) {  //0x0B specifies that we need to kill the process at index bx (project 5)
    return  kill(bx);
  }else if (ax == 0x0C) {  //0x0B specifies that we need to kill the process at index bx (project 5)
    return interrupt(0x08,0,0,0);
  }else{
    return -1;
  }
}

/*
 * Reads a Sector from Disk via the BIOS (Interrupt 0x13)
 */

int readSector(char *buf, int absSector) {
  int relSector;
  int head;
  int track;
  relSector = mod(absSector, 18) + 1;
  head = mod(absSector /18, 2);
  track = ( absSector / 36 );
  interrupt(0x13, 0x02 * 256 + 0x01, buf, track * 256 + relSector, head * 256 + 0x00);
  return 1;
}

/*
 * Helper method that carries out the function of the modulus operator. It 
 * yields the remainder when the first operand is divided by the second
 */

int mod(int dividend, int divisor) {
  while (dividend >= divisor) {
    dividend = dividend - divisor;
  }
  return dividend;
}

/*
 * Read an entire string by utilizing the readChar method that reads one 
 * character at a time from the Keyboard via the BIOS (Interrupt 0x16)
 *
 * Includes Bonus 1 feature: the calling program can specify the maximum
 * number of characters that will be placed into the provided buffer
 */

int readString(char *buf, int maxChar) {
  int i = 0;
  char charRead[2];

  char enter = 0x0D;
  char ch;
  charRead[1] = 0x00;

  ch = 0x00;
  ch = readChar();
  while (ch != enter) {
    //if user hits backspace, remove the deleted character from the buf as well as the screen
    if (ch==0x08) {
      i--; //move index one step back
      interrupt(0x10, 0x0E * 256 +0x08, 0, 0, 0); //move cursor one step back
      buf[i]=' '; //replace the deleted character with a space
      interrupt(0x10, 0x0E * 256 +buf[i], 0, 0, 0); //print out space on screen
      interrupt(0x10, 0x0E * 256 +0x08, 0, 0, 0); //move cursor one step back again
    } else if (i >= maxChar) {
      break;
    } else { //when we do not hit backspace or haven't reached the limit
      buf[i] = ch;
      charRead[0]=ch;
      printString(charRead);
      i++;
    }
    ch = readChar();
  }
  while(ch != enter){
    ch = readChar();
   }
  buf[i] = 0x00;
  return i;
}

/*
 * Read one character at a time from the Keyboard via the BIOS (Interrupt 0x16)
 */

int readChar() {
  return interrupt(0x16, 0x00, 0, 0, 0);
}

/*
 * Display a string to the screen via the BIOS (Interrupt 0x10)
 */

int printString(char *str) {
  int i = 0;
  while(str[i] != '\0') {
    char al = str[i];
    char ah = 0x0E;
    int ax = ah * 256 + al;
    interrupt(0x10, ax, 0, 0, 0);
    i++;
  }
  return i;
}

/* Functions for project 1 */

/*
 * Display a string in a specified color at a specified location on the 
 * screen
 */

void putChar(int col, int row, char character, char color) {
  putInMemory(0xB000, 0x8000 + (row * 160) + (col * 2), character);
  putInMemory(0xB000, 0x8000 + (row * 160) + (col * 2) + 1, color);
}

/*
 * Display a string in a specified color at a specified location on the 
 * screen
 */

void putStr(int col, int row, char character[], char color) {
  int i = 0;
  while (character[i] != '\0') {
      putChar(col, row, character[i], color);
      i++;
      col++;
    }
}
