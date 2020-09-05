MEMORY
{
    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    ram   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(ram) + LENGTH(ram) - 4K;

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        _stext = .;
        KEEP(*(.vector*))
        *(.text*)
        _etext = .;
    } > flash

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
        _sidata = .;
    } > flash

    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > flash

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    .heap :
    {
        . = ALIGN(4);
        heap_size = 4K;
        PROVIDE(end = .);
        PROVIDE(_heap_start = end);
        . = . + heap_size;
        PROVIDE(_heap_end = .);
    } > ram
}

