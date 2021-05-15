#include <stdint.h>
#include "../../../stivale/stivale2.h"

#include <tty.h>
#include <main.h>

char *video = 0xB8000;

struct simpletty_info_t {
    int cols;
    int rows;
};

static struct simpletty_info_t simpletty_info = {
    80,
    24
};

void simpletty_write(tty_driver_t *tty, char *s) {
    while (*s) {
        *video++ = *s++;
        *video++ = 0x0F;
    }
}

void simpletty_clear(tty_driver_t *tty) {

}

void _cstart(struct stivale2_struct *stivale2_info) {
    chosen_tty.write = simpletty_write;
    chosen_tty.clear = simpletty_clear;
    chosen_tty.extra = &simpletty_info;
    kernel_main();
}