#include <stdint.h>
#include <bootstrap.h>
#include <panic.h>

static uint8_t bs[131072];
static uintptr_t bs_counter = 0;
static uint8_t *pos = &bs;

void *bs_alloc(uintptr_t length) {
    bs_counter += length;
    uint8_t *where = pos;
    pos = &pos[length];
    if (pos > (bs + sizeof(bs))) {
        PANIC("bootstrap out of memory");
    }
    return where;
}

uintptr_t bs_reset_counter() {
    uintptr_t old = bs_counter;
    bs_counter = 0;
    return old;
}