ENTRY(kernel_main)
SECTIONS {
    . = 0x10000;       /* Адрес загрузки ядра */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}