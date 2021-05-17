#include <stdint.h>

void print_hex(uint8_t x) {
    x &= 0x0f;
    char *table = "0123456789abcdef";
    asm volatile ("outb %0, $0xE9" :: "r"(table[x]));
}

void print_byte(uint8_t x) {
    print_hex(x >> 4);
    print_hex(x);
}

void print_word(uint16_t x) {
    print_byte(x >> 8);
    print_byte(x);
}

void print_dword(uint32_t x) {
    print_word(x >> 16);
    print_word(x);
}

void print_qword(uint64_t x) {
    print_dword(x >> 32);
    print_dword(x);
}