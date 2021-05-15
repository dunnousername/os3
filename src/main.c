#include <main.h>
#include <tty.h>

void kernel_main() {
    chosen_tty.write(&chosen_tty, "Hello, world!");
    while(1);
}