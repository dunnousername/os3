#include "../../../stivale/stivale2.h"
#include <stdint.h>

struct stivale2_header_tag_terminal _stivale2_tag0;

static uint8_t stack[8192];

struct stivale2_header __attribute__(( section(".stivale2hdr") )) _stivale2_header = {
    0,
    (uintptr_t)stack + sizeof(stack),
    0,
    &_stivale2_tag0
};

struct stivale2_header_tag_terminal _stivale2_tag0 = {
    0xa85d499b1823be72,
    0,
    0
};