#include <stdint.h>

void *memcpy(void *to, void *from, uintptr_t len);

void *memset(void *mem, uint8_t c, uintptr_t len);

uintptr_t strlen(char *str);

int strcmp(char *s1, char *s2);