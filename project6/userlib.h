#ifndef U_H_
#define U_H_

//printString
int printString(char *str);

//readChar
int readChar();

//readString
int readString(char *buf, int maxChar);

//readfile
int readfile(char *filename, char *buf);

//readSector
int readSector(char *buf, int absSector);

//executeProgram
int executeProgram(char *name, int segment);

//terminate
void terminate();

//deleteFile
int deleteFile(char* filename);

//writeFile
int writeFile(char *filename, char *buffer, int sectors);

//printInt
int printInt(int num);

//clearBuffer
void clearBuffer(char* buffer);

//modulus operator
int mod(int dividend, int divisor);

//yield
void yield();

//show processes
void showProcesses();

//kill
int kill(int segment);

//findFileBonus
int findFileBonus(char *filename);

#endif
  
