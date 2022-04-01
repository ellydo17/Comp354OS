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
int readString(char *buf) {
  return interrupt(0x21, 0x01, buf, 0, 0);
}

//readfile
int readfile(char *filename, char *buf) {
  return interrupt(0x21, 0x03, filename, buf, 0);
}

//executeProgram
int executeProgram(char *name, int segment) {
  return interrupt(0x21, 0x04, name, segment, 0);
}

//terminate
void terminate() {
  return interrupt(0x21, 0x05, 0, 0, 0);
}
