/*
 * @author Elly Do, Sweta Tamrakar
 * @date February 15, 2022
 */

void putStr(int col, int row, char character[], char color);

void putChar(int col, int row, char character, char color);

int printString(char *str);

int readChar();

int readString(char *buf);

int readSector(char *buf, int absSector);

int handleInterrupt21(int ax, int bx, int cx, int dx);

int printInt(int num);

int getNumDigits(int num);

void reverse(char* numStr, int numDigits);

char* itoa(int num);

int readfile(char *filename, char *buf);

int findFile(char *filename, char *diskSector);

typedef char byte;

struct dirEntry{
  char name[6];
  byte sectors[26];
};

struct directory{
  struct dirEntry entries[16];
}

void main() {
  //tests for project 3

  //tests for "Loading and Printing a File"
  char buffer[13312]; /* the maximum size of a file*/
  makeInterrupt21();
  /*read the file into buffer*/
  interrupt(0x21, 0x03, "messag\0", buffer, 0);
  /*print out the file*/
  interrupt(0x21, 0x00, buffer, 0, 0);
  
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

  //for readString()
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

/*
 * Loading and printing file
 */

int readfile(char *filename, char *buf){
  int totalSectorsRead = 0;
  int fileIndex = -1;
  int i = 0;
  char diskSector[512]; //address of buffer into which data will be placed
  char content;
  int bufIndex = 0;

  struct directory diskEntries;
  
  readSector((char *)&diskEntries, 2);
  
  //read the file from disk sector, if it is read successfully, it will return 1
  if(readSector(diskSector, 2)!=1){ //file is read from sector 2
    printString("file cannot be read from disk sector\0"); //file may be corrupt or not have permission
  }
  //helper method to find the file in disk
  fileIndex = findFile(filename, diskSector);
  printString("fileIndex is:\0");
  printString(fileIndex);
  printString("\n\0");
  
  //read contents from the file if file was found
  if(fileIndex != -1){ //file found
    printString("file was found\0");
    for(i=6; i<32; i++){
      content = diskSector[fileIndex+i]; //content is the next sector to read
      if(content=='\0'){
	break;
      }
      //put the content into buf: content contains the next sector index to read and each sector has 512 bytes, so once a sector is read, we want to increment the index of buf by 512 bytes.
      readSector(buf+bufIndex, content);
      
      printString("index is ");
      printString(i);
      printString("\n\0");
      printString(buf);
      printString("\n\0");
      
      totalSectorsRead++;
      bufIndex = bufIndex + 512;
    }
  }else{
    printString("file not found\0");
    return -1;
  }

  printString("successfully read file\0");
  return totalSectorsRead;
}

int findFile(char *filename, char *diskSector){
  int i=0;
  int j=0;
  
  for(i=0; i<16; i++){
    for(j=0; j<6; j++){
      if(diskSector[(i*32)+j]!=filename[j]){
	break;
      }
    }
    if(j==6){ //found file
      return i; //this is the index of the file in the disk sector
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
  if(num<0){
    length = 1;
  }
  while(num!=0){
    length++;
    num=num/10;
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
 * Modify the handleInterrupt21 function to create system calls that allow us to
 * print a string, read a character, and read a string using the printString, 
 * readChar, and readString functions
 */

int handleInterrupt21(int ax, int bx, int cx, int dx){
  if(ax==0x00){ //0x00 specifies that we need to print a string
    return printString(bx);
  }else if(ax==0x11){ //0x11 specifies that we need to read a character
    char ch = readChar();
    char* buf = bx;
    buf[0] = ch;
    return 1;
  }else if(ax==0x01){ //0x01 specifies that we need to read a string (read characters until ENTER is pressed)
    return readString(bx);
  }else if(ax==0x03){ //0x03 specifies that we need to read the contents of a file into a buffer
    return readfile(bx,cx);
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
  charRead[1]=0x00;

  ch=0x00;
  ch=readChar();
  while (ch != enter) {
    //if user hits backspace, remove the deleted character from the buf as well as the screen
    if(ch==0x08){
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
