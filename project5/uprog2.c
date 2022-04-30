void main() {
  enableInterrupts();
  interrupt(0x21, 0, "Elly and Sweta!\r\n\0", 0, 0);
  interrupt(0x21, 0x05, 0, 0, 0);
}
