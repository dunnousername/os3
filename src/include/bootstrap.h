#ifndef _BOOTSTRAP_H_
#define _BOOTSTRAP_H_

#include <stdint.h>

void *bs_alloc(uintptr_t length);

uintptr_t bs_reset_counter();

#endif