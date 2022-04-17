#include "userlib.h"

//printString
int printString(char *str) {
  return interrupt(0x21, 0x00, str, 0, 0);
}

//readChar
int readChar() {
  char ch[1];
  interrupt(0x21, 0x11, ch, 0, 0); //double-check bx later, probably we don't need ch because buffer is empty at the beginning. Or we don't need ch for the readChar method in the InterruptHander21 in kernel.c
  return ch;
}

//readString
int readString(char *buf, int maxChar) {
  return interrupt(0x21, 0x01, buf, maxChar, 0);
}

//readfile
int readfile(char *filename, char *buf) {
  return interrupt(0x21, 0x03, filename, buf, 0);
}

//readSector
int readSector(char *buf, int absSector){
  return interrupt(0x21, 0x02, buf, absSector, 0);
}

//executeProgram
int executeProgram(char *name, int segment) {
  return interrupt(0x21, 0x04, name, segment, 0);
}

//terminate
void terminate() {
  return interrupt(0x21, 0x05, 0, 0, 0);
}

//deleteFile
int deleteFile(char* filename){
  return interrupt(0x21, 0x07, filename, 0, 0);
}

//writeFile
int writeFile(char *filename, char *buffer, int sectors){
  return interrupt(0x21, 0x08, filename, buffer, sectors);
}

//clearBuffer
void clearBuffer(char* buffer){
  int i = 0;
  while (i < 13312 && buffer[i] != '\0') {
    buffer[i] = 0x00;
    i++;
  }
}

//modulus operator
int mod(int dividend, int divisor) {
  while (dividend >= divisor) {
    dividend = dividend - divisor;
  }
  return dividend;
}

//print an integer value
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
