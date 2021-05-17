#include <stdint.h>

/* technically loadable and callable, right? */
#define MODULE_MAGIC ((((uint64_t) 0x10ADAB1E) << 32) | (((uint64_t) 0xCA11AB1E) << 0))

typedef struct {
    char *name;
    void *symbol;
} __attribute__(( packed )) module_symbol_t;

typedef struct {
    uint64_t magic;
    void (*init)(void *(*kdlsym)(char *));
    char *name;
    /* 8-bit value. lower nice is loaded first */
    uint8_t nice;
    module_symbol_t symbols[];
} __attribute__(( packed )) module_info_t;

typedef struct {
    module_info_t *start;
    uintptr_t length;
    int loaded;
} __attribute__(( packed )) module_desc_t;

extern void load_module(module_desc_t);

extern void commit_modules();

extern void *kdlsym(char *);