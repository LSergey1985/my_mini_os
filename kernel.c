#define VIDEO_MEMORY 0xB8000  // Адрес видеопамяти

void clear_screen() {
    unsigned char* video_memory = (unsigned char*) VIDEO_MEMORY;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';      // Символ пробела
        video_memory[i + 1] = 0x07; // Атрибут текста (светло-серый на чёрном)
    }
}

void print_string(const char* str) {
    unsigned char* video_memory = (unsigned char*) VIDEO_MEMORY;
    while (*str) {
        *video_memory++ = *str++;  // Символ
        *video_memory++ = 0x07;    // Атрибут текста
    }
}

void kernel_main() {
    clear_screen();
    print_string("Welcome to Simple DOS!");
    print_string("\n> ");
}