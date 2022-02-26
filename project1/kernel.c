void putStr(int col, int row, char character[], char color);

void putChar(int col, int row, char character, char color);

void main() {
  putStr(37, 14, "Elly Do", 0x4F);
  
  //0x4F is the hexadecimal for 01001111, which means white text on red
  //background
  putChar(35, 13, 'H', 0x4F);
  putChar(36, 13, 'E', 0x4F);
  putChar(37, 13, 'L', 0x4F);
  putChar(38, 13, 'L', 0x4F);
  putChar(39, 13, 'O', 0x4F);
  putChar(40, 13, ' ', 0x4F);
  putChar(41, 13, 'W', 0x4F);
  putChar(42, 13, 'O', 0x4F);
  putChar(43, 13, 'R', 0x4F);
  putChar(44, 13, 'L', 0x4F);
  putChar(45, 13, 'D', 0x4F);
  

  putInMemory(0xB000, 0x8140, 72);
  putInMemory(0xB000, 0x8141, 0x0F);
  putInMemory(0xB000, 0x8142, 69);
  putInMemory(0xB000, 0x8143, 0x0F);
  putInMemory(0xB000, 0x8144, 76);
  putInMemory(0xB000, 0x8145, 0x0F);
  putInMemory(0xB000, 0x8146, 76);
  putInMemory(0xB000, 0x8147, 0x0F);
  putInMemory(0xB000, 0x8148, 79);
  putInMemory(0xB000, 0x8149, 0x0F);
  putInMemory(0xB000, 0x814A, 32);
  putInMemory(0xB000, 0x814B, 0x0F);
  putInMemory(0xB000, 0x814C, 87);
  putInMemory(0xB000, 0x814D, 0x0F);
  putInMemory(0xB000, 0x814E, 79);
  putInMemory(0xB000, 0x814F, 0x0F);
  putInMemory(0xB000, 0x8150, 82);
  putInMemory(0xB000, 0x8151, 0x0F);
  putInMemory(0xB000, 0x8152, 76);
  putInMemory(0xB000, 0x8153, 0x0F);
  putInMemory(0xB000, 0x8154, 68);
  putInMemory(0xB000, 0x8155, 0x0F);

  while(1) {
  /*infinite loop*/
  }
}

void putChar(int col, int row, char character, char color) {
  putInMemory(0xB000, 0x8000 + (row * 160) + (col * 2), character);
  putInMemory(0xB000, 0x8000 + (row * 160) + (col * 2) + 1, color);
}

void putStr(int col, int row, char character[], char color) {
  int i = 0;
  while (character[i] != '\0') {
      putChar(col, row, character[i], color);
      i++;
      col++;
    }
}
