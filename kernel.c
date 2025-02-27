// kernel.c
#include <stdint.h>

// VGA
#define VGA_BASE 0xB8000
enum vga_color { BLACK=0, GREEN=2, WHITE=15 };

void print(char *str, uint8_t color) {
    volatile char *vga = (volatile char*)VGA_BASE;
    while (*str) {
        *vga++ = *str++;
        *vga++ = color;
    }
}

// Прерывания и клавиатура
#define IDT_SIZE 256
struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idtp;

extern void load_idt();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].flags = flags | 0x60;
    idt[num].zero = 0;
}

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idtp.base = (uint32_t)&idt;
    load_idt();
}

// ... предыдущий код kernel.c ...

// Объявить обработчики прерываний
extern void irq0();
extern void irq1();

void init_idt() {
    // Настройка обработчика таймера (IRQ0)
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);

    // Настройка обработчика клавиатуры (IRQ1)
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);

    // Загрузка IDT
    idtp.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idtp.base = (uint32_t)&idt;
    load_idt(&idtp);  // Передаём указатель на структуру
}

// ... остальной код ...

// Таймер и многозадачность
#define MAX_TASKS 4
struct task {
    uint32_t esp;
    uint8_t active;
};
struct task tasks[MAX_TASKS];
uint8_t current_task = 0;

void task_switch() {
    // Сохраняем текущий контекст и переключаем задачи
}

// Точка входа
void kernel_main() {
    print("MyOS Booted!\n", GREEN);
    init_idt();
    // Инициализация клавиатуры, таймера, задач
    while(1) {
        // Обработка команд
    }
}
