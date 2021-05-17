[BITS 64]

segment .text
extern _cstart
global _start

_start:
    mov al, '.'
    out 0xE9, al
    call _cstart
