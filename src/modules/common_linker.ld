SECTIONS {
    .module_header : {
        KEEP(*(.module_header))
    }

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .note : {
        *(.note*)
    }
    
    .bss : {
        *(.bss*)
    }
}