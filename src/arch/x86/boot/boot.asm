[BITS 64]

segment .text
extern _cstart
global _start

_start:
    push rdi
    call _cstart
