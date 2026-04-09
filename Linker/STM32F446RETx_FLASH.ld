ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

_Min_Heap_Size  = 0x0;
_Min_Stack_Size = 0x200;

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.ARM.extab*)
        *(.ARM.exidx*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT>FLASH

    _sidata = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE(end = .);
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >SRAM

    /DISCARD/ :
    {
        *(.ARM.attributes)
    }
}