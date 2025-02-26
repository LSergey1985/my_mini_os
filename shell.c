#include "string.c"

void execute_command(const char* command) {
    if (strcmp(command, "help") == 0) {
        print_string("\nAvailable commands: help, reboot");
    } else if (strcmp(command, "reboot") == 0) {
        print_string("\nRebooting...");
        __asm__ volatile ("int $0x19");  // Перезагрузка
    } else {
        print_string("\nUnknown command.");
    }
}

void shell() {
    char input[100];
    int index = 0;

    while (1) {
        char key = getchar();
        if (key == '\n') {
            input[index] = '\0';
            execute_command(input);
            print_string("\n> ");
            index = 0;
        } else {
            input[index++] = key;
        }
    }
}