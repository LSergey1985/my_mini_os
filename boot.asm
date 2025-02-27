; boot.asm
bits 16
org 0x7C00

start:
    jmp main

load_kernel:
    ; Загрузка секторов ядра
    ret

main:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    call load_kernel
    ; Переход в защищённый режим
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:pm_start

bits 32
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov esp, 0x90000
    call kernel_main
    hlt

gdt:
    ; GDT дескрипторы
gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt

times 510-($-$$) db 0
dw 0xAA55