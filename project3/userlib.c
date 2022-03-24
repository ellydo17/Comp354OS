void main() {
  if (input == "print\0") { //printString
    interrupt(0x21, 0x00, 0, 0, 0);
  } else if (input == "read char\0") { //readChar
    interrupt(0x21, 0x11, 0, 0, 0);
  } else if (input == "read string\0") { //readString
    interrupt(0x21, 0x01, bx, 0, 0);
  } else if (input == "read file\0") { //readfile
    interrupt(0x21, 0x03, 0, 0, 0);
  } else if (input == "execute prog\0") { //executeProgram
    interrupt(0x21, 0x04, 0, 0, 0);
  } else if (input == "terminate\0") { //terminate
    interrupt(0x21, 0x05, 0, 0, 0);
  }
}
