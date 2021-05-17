#include <main.h>
#include <tty.h>
#include <modules.h>

void kernel_main() {
    commit_modules();
    ((void (*)(char *)) kdlsym("debug_puts"))("Hello, world!");
    chosen_tty->write(chosen_tty, "Hello, world!");
    while(1);
}