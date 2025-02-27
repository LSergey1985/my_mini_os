; idt.asm
bits 32

global load_idt

load_idt:
    mov eax, [esp + 4]  ; Получаем указатель на idt_ptr
    lidt [eax]          ; Загружаем IDTR
    ret
