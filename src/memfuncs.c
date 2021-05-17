#include <stdint.h>
#include <memfuncs.h>

void *memcpy(void *to, void *from, uintptr_t len) {
    for (uintptr_t i = 0; i < len; i++) {
        ((uint8_t *) to)[i] = ((uint8_t *) from)[i]; 
    }

    return to;
}

void *memset(void *mem, uint8_t c, uintptr_t len) {
    for (uintptr_t i = 0; i < len; i++) {
        ((uint8_t *) mem)[i] = c;
    }

    return mem;
}

uintptr_t strlen(char *str) {
    uintptr_t i = 0;
    while (*str++) i++;
    return i;
}

int strcmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}