#include <panic.h>
#include <_debug.h>

void panic(char *file, char *func, char *line, char *reason) {
    dputs("!!! PANIC !!!\n");
    dputs("\nfile: ");
    dputs(file);
    dputs("\nfunc: ");
    dputs(func);
    dputs("\nline: ");
    dputs(line);
    dputs("\nreason: ");
    dputs(reason);
    dputs("\nExecution will stop, and the processor will go into an infinite loop or halt until it is reset.\n");
    dputs("\n");
    dputs("!!! PANIC !!!\n");
    while(1);
}