#include <modules.h>

static void putch(char character) {
    asm volatile ("outb %0, $0xE9" :: "r"(character));
}

static void puts(char *data) {
    while (*data) {
        putch(*data++);
    }
}

static void _debug_initmod(char *modname) {
    puts("Loaded module ");
    puts(modname);
    puts(".\n");
}

static void *(*_kdlsym)(char *);

static void init(void *(*__kdlsym)(char*)) {
    _kdlsym = __kdlsym;
}

module_info_t __attribute__(( section(".module_header") )) _start = {
    MODULE_MAGIC,
    init,
    "arch-x86-port_e9",
    0,
    {
        { "_debug_initmod", _debug_initmod },
        { "debug_puts", puts },
        { "debug_putch", putch }
    },
};