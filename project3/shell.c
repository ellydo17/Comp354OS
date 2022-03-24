void main() {
  char line[80];
  char ch[1];
  while(1){
    interrupt(0x21, 0, "Shell>\r\n\0", 0, 0);
    interrupt(0x21, 0x01, line, 0, 0);
    interrupt(0x21, 0, "Unrecognized command\r\n\0", 0, 0);
  }
}
