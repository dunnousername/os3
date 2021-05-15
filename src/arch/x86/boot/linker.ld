ENTRY(_start)

SECTIONS {
    __higher_half = 0xffffffff80000000;

    . = __higher_half + 2M;

    .text : ALIGN(0x1000) {
        *(.text)
    }

    .stivale2hdr : ALIGN(0x1000) {
        *(.stivale2hdr)
    }

    .rodata : ALIGN(0x1000) {
        *(.rodata)
    }

    .data : ALIGN(0x1000) {
        *(.data)
    }

    .bss : ALIGN(0x1000) {
        *(.bss)
    }
}