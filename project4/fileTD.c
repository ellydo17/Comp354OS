void main() {
  interrupt(0x21, 0, "You can delete this file!\r\n\0", 0, 0);
  interrupt(0x21, 0x05, 0, 0, 0);
}
