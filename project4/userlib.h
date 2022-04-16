#ifndef U_H_
#define U_H_

//printString
int printString(char *str);

//readChar
int readChar();

//readString
int readString(char *buf);

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

#endif
  
