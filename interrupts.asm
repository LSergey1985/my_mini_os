; interrupts.asm
bits 32

global irq0, irq1

; Обработчик таймера (IRQ0)
irq0:
    pushad
    ; Вызов обработчика на C
    call timer_handler
    popad
    iretd

; Обработчик клавиатуры (IRQ1)
irq1:
    pushad
    ; Вызов обработчика на C
    call keyboard_handler
    popad
    iretd

; Пустые заглушки для C-кода
timer_handler:
    ret

keyboard_handler:
    ret
