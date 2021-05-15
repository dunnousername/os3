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

static void simpletty_write(tty_driver_t *tty, char *s) {
    while (*s) {
        *video++ = *s++;
        *video++ = 0x0F;
    }
}

static void simpletty_clear(tty_driver_t *tty) {

}

struct stivale2_tag *parse_stivale(struct stivale2_tag *tag) {
    if (!tag) {
        return (void *) 0;
    }

    switch (tag->identifier) {
        default:
            break;
    }

    if (tag->next) {
        return (void *) tag->next;
    }

    return (void *) 0;
}

void _cstart(struct stivale2_struct *stivale2_info) {
    chosen_tty.write = simpletty_write;
    chosen_tty.clear = simpletty_clear;
    chosen_tty.extra = &simpletty_info;

    if (stivale2_info->tags) {
        struct stivale2_tag *current = (void *) stivale2_info->tags;
        while (current = parse_stivale(current));
    }

    kernel_main();
}