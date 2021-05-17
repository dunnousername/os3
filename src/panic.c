#include <stdint.h>
#include <panic.h>
#include <_debug.h>

void panic(const char *file, const char *func, const char *line, const char *reason, uint64_t extra) {
    dputs("!!! PANIC !!!\n");
    dputs("\nfile: ");
    dputs(file);
    dputs("\nfunc: ");
    dputs(func);
    dputs("\nline: ");
    dputs(line);
    dputs("\nreason: ");
    dputs(reason);
    dputs("\nextra: ");
    print_qword(extra);
    dputs("\nExecution will stop, and the processor will go into an infinite loop or halt until it is reset.\n");
    dputs("\n");
    dputs("!!! PANIC !!!\n");
    while(1);
}