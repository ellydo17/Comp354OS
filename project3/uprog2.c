void main() {
  interrupt(0x21, 0, "I'm back!\r\n\0", 0, 0);
  while(1);
}
