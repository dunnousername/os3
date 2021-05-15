SECTIONS {
    ENTRY(_start)

    . = 1M;

    .text : ALIGN(0x1000) {
        *(.text)
    }

    .stivale2hdr : ALIGN(0x1000) {
        *(.stivale2hdr)
    }

    .data : ALIGN(0x1000) {
        *(.data)
    }

    .bss : ALIGN(0x1000) {
        *(.bss)
    }
}