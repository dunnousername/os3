#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <stdint.h>

void print_hex(uint8_t x);
void print_byte(uint8_t x);
void print_word(uint16_t x);
void print_dword(uint32_t x);
void print_qword(uint64_t x);

void dputc(char c);
void dputs(char *s);

#endif