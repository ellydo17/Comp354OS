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
