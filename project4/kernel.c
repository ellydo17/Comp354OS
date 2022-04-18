/*
 * @author Elly Do, Sweta Tamrakar
 * @date February 15, 2022
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

int executeProgram(char *name, int segment);

int writeSector(char *buf, int absSector);

int deleteFile(char* filename);

int writeFile(char *filename, char *buffer, int sectors);

void main() {
  //tests for project 4

  //tests for "TextEditor"
  /*
  makeInterrupt21();
  interrupt(0x21, 0x04, "textEditor\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  */
  
  //tests for "Writing a file" - debugging
  //char buffer[13312];
  //makeInterrupt21();
  //interrupt(0x21, 0x07, "happy1\0", 0, 0);
  /*
  deleteFile("happy1\0");
  printString("deleted file\r\n\0");
  */
  
  /*
  char buffer[13312];
  readfile("apple\0", buffer);
  printString(buffer);
  */
  
  //tests for "Writing a file"
  /* For some reasons, if we do writeFile then readfile twice in a row, we cannot print out the message from the file using the second buffer. If we do each set one by one, the message is printed out"
   */
  /*
  char buffer[13312];
  char buffer2[13312];
  readfile("happy1\0", buffer);
  printString(buffer);
  writeFile("happyT\0", buffer, 3);
  readfile("happyT\0", buffer2);
  printString(buffer2);
  */

  
  //char buffer[13312];
  /*
  writeFile("testWF\0", "writing to testWF file, if this prints out, it means that the text was successfully written into the file.", 5);
  //writeFile("testWF\0", "overriding testWF file, if this prints out, overriding is working.", 3);
  readfile("testWF\0", buffer);
  printString(buffer);
  printString("Done.\0");
  */
  
  /*
  //load the new file called happy1.txt
  char buffer1[13312]; // the maximum size of a file
  char buffer2[13312]; // the maximum size of a file
  makeInterrupt21();
  //read the happy1 file into buffer
  interrupt(0x21, 0x03, "happy1\0", buffer1, 0);
  //print out the contents from happy1 file
  //interrupt(0x21, 0x00, "happy1 file says \0", 0, 0);
  interrupt(0x21, 0x00, buffer1, 0, 0);
  interrupt(0x21, 0x00, "\r\n\0", 0, 0);
  
  
  //write the file to disk
  interrupt(0x21, 0x08, "happy2\0", buffer1, 1);
  printString("wrote the file to disk\r\n\0");
  
  
   //read the file into buffer2
  interrupt(0x21, 0x03, "happy2\0", buffer2, 0);
  //print out the contents from buffer2
  interrupt(0x21, 0x00, buffer2, 0, 0);
  */
  
  //tests for "Deleting a File"
  /*
  //load new file first, will delete it later
  char buffer[13312]; // the maximum size of a file
  makeInterrupt21();
  //read the file into buffer
  interrupt(0x21, 0x03, "delete\0", buffer, 0);
  //print out the file
  interrupt(0x21, 0x00, buffer, 0, 0);
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
  
  makeInterrupt21();
  interrupt(0x21, 0x04, "shell\0", 0x2000, 0);
  interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
  
  
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
  
  //tests for project 2
  
  //test for bonus 2
  /*
  int num = 12345;
  printInt(num);
  */
  
  
  //test for bonus 1
  /*
  char line[20];
  printString("Enter a line: \0");
  readString(line, 10);
  printString("\n\0");
  printString(line);
  */
  
  
  //test for "Creating printString, readChar, and readString System Calls"
  /*
  char line[80];
  char ch[1];

  makeInterrupt21(); //setup ISR for interrupt 0x21

  interrupt(0x21, 0x00, "Type>\0", 0, 0);
  interrupt(0x21, 0x11, ch, 0, 0);
  line[0] = ch[0];
  line[1] = 0x00;

  interrupt(0x21, 0x00, line, 0, 0);
  */
  
  //test for "Reading a Sector from Disk via the BIOS (Interrupt 0x13)
  /*
  char buffer[512];
  readSector(buffer, 30);
  printString(buffer);
  */

  //test for "Reading from the Keyboard via the BIOS (Interrupt 0x16)

  //for readChar()
  /*char *buf = "*****\0";
  char ch;
  
  // just read the character.
  printString("Type a char: \0");
  ch = readChar();
  buf[2] = ch;
  printString("Read: \0");
  printString(buf);
  printString("\n\r\0");
  */

  //for readString() - original
  /*
  char line[20];
  printString("Enter a line: \0");
  readString(line);
  printString("\n\0");
  printString(line);
  */

   //test for "Printing to the Screen via the BIOS (Interrupt 0x10)
  /*printString("Hello World\0"); */
  
  //tests for project 1
  /*
  putStr(37, 14, "Elly Do", 0x4F);
  
  //0x4F is the hexadecimal for 01001111, which means white text on red
  //background
  putChar(35, 13, 'H', 0x4F);
  putChar(36, 13, 'E', 0x4F);
  putChar(37, 13, 'L', 0x4F);
  putChar(38, 13, 'L', 0x4F);
  putChar(39, 13, 'O', 0x4F);
  putChar(40, 13, ' ', 0x4F);
  putChar(41, 13, 'W', 0x4F);
  putChar(42, 13, 'O', 0x4F);
  putChar(43, 13, 'R', 0x4F);
  putChar(44, 13, 'L', 0x4F);
  putChar(45, 13, 'D', 0x4F);
  

  putInMemory(0xB000, 0x8140, 72);
  putInMemory(0xB000, 0x8141, 0x0F);
  putInMemory(0xB000, 0x8142, 69);
  putInMemory(0xB000, 0x8143, 0x0F);
  putInMemory(0xB000, 0x8144, 76);
  putInMemory(0xB000, 0x8145, 0x0F);
  putInMemory(0xB000, 0x8146, 76);
  putInMemory(0xB000, 0x8147, 0x0F);
  putInMemory(0xB000, 0x8148, 79);
  putInMemory(0xB000, 0x8149, 0x0F);
  putInMemory(0xB000, 0x814A, 32);
  putInMemory(0xB000, 0x814B, 0x0F);
  putInMemory(0xB000, 0x814C, 87);
  putInMemory(0xB000, 0x814D, 0x0F);
  putInMemory(0xB000, 0x814E, 79);
  putInMemory(0xB000, 0x814F, 0x0F);
  putInMemory(0xB000, 0x8150, 82);
  putInMemory(0xB000, 0x8151, 0x0F);
  putInMemory(0xB000, 0x8152, 76);
  putInMemory(0xB000, 0x8153, 0x0F);
  putInMemory(0xB000, 0x8154, 68);
  putInMemory(0xB000, 0x8155, 0x0F);
  */

  while(1) {
  /*infinite loop*/
  }
}

/* Functions for project 4 */

/*
 * Writing a File
 */

int writeFile(char * filename, char * buffer, int sectors){

  char diskMap[512];
  struct directory diskDir;

  int dirEntry, i,j,idx, residue;
  int sectorCounter = 0;//index of sector in the entry
  int fileNameLen = 0;

  int sectorNum;
  int oldSector;

  char sectorBuffer[512];

  int flag = -1; // to see if it found the free entry

  int bufferIndex = 0;;

  if (sectors > 26) {
    sectors = 26;
  }

  //performing overwriting if the file already exists. 
  deleteFile(filename);
  
  readSector(diskMap,1);
  readSector(&diskDir,2);
  
  //finding an empty entry in the Disk Directory
  for(dirEntry = 0; dirEntry < 16; dirEntry++){
    if(diskDir.entries[dirEntry].name[0] == 0x00){
      flag = 1;
      break;
    }
  }

  //there is no empty entry found
  if(flag == -1){
    printString("There is no Disk Directory entry available for the new file.\0");
    return -1;
  }

  //get the length of the file name
  while(filename[fileNameLen] != '\0' && filename[fileNameLen] != 0x00){
    fileNameLen++;
  }

  /*Assign the filename into the directory free entry*/
  for(j = 0; j < fileNameLen; j++){
    diskDir.entries[directoryEntry].name[j] = filename[j];
  }

  if(fileNameLen < 6){
    residue = 6 - fileNameLen;

    for(j = 0; j < residue; j++){
      //fill the residues with 0x00
      diskDir.entries[directoryEntry].name[j+fileNameLen] = 0x00; 
    }
  }

  /*Write the file contents into the sectors consisting of the file*/
  for(sectorCounter = 0; sectorCounter < sectors; sectorCounter++){
    sectorNum = 0;

    //find an empty space in diskMap, the empty space index = sectorNum
    while(diskMap[sectorNum] != 0x00){
      sectorNum++;
    }

    //if there is no available space in the diskMap, return -2
    if(sectorNum >= 512){
      printString("Disk Map contains fewer sectors than requested!\0");
      return -2;
    }

    //free up old used space
    oldSector = diskDir.entries[directoryEntry].sectors[sectorCounter];
    diskMap[oldSector] = 0x00;

    //mark new space as occupied
    diskMap[sectorNum] = 0xFF;
    //save the new space used for the file in the file's sector structure
    diskDir.entries[directoryEntry].sectors[sectorCounter] = sectorNum;
 
    for(j = 0; j < 512; j++){
      sectorBuffer[j] = buffer[bufferIndex];
      bufferIndex++;
    }

    writeSector(sectorBuffer, sectorNum);
  }

  writeSector(diskMap,1);
  writeSector(&diskDir,2);

  return sectorNum;
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

  printString("running delete method\r\n\0");
  
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
    printString("Error: file not found\0");
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
  printString("I'm back!\r\n\0");

  //Run the shell program again
  executeProgram("shell\0", 0x2000);
}

/*
 * Loading and executing a program
 */

int executeProgram(char *name, int segment){
  char buffer[13312];
  int i = 0;
  int totalSectorsRead = readfile(name, buffer);
  
  if (totalSectorsRead == -1) { //if program/file not found
    return -1;
  }else{  //if program/file found
    //check for invalid segment, if segment is invalid, return -2
    if (mod(segment, 0x1000) != 0 || segment == 0x0000 || segment == 0x1000 || segment >= 0xA000) {
      printString("Invalid segment\0");
      return -2;
    } else { //segment is valid
      //iterate through the buffer and place each element from the buffer into the memory segment
      while (i < (totalSectorsRead*512)) {
	putInMemory(segment, i, buffer[i]);
	i++;
      }
    }
  }
  
  launchProgram(segment);
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
  char *str = itoa(num, numDigits);
  
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
    return executeProgram(bx, cx);
  } else if (ax == 0x05) {  //0x05 specifies that we need to terminate a user program (project 3)
    return terminate();
  }else if (ax == 0x07) {  //0x05 specifies that we need to terminate a user program (project 3)
    return  deleteFile(bx);
  }else if (ax == 0x08) {  //0x05 specifies that we need to terminate a user program (project 3)
    return  writeFile(bx,cx,dx);
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
