unsigned char getchar() {
    unsigned char key;
    __asm__ volatile ("inb $0x60, %0" : "=a"(key));  // Чтение скан-кода клавиатуры
    return key;
}