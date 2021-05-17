#ifndef _PANIC_H_
#define _PANIC_H_

#include <stdint.h>

#define _xstr(s) _str(s)
#define _str(s) #s

#define PANIC(reason) PANIC2(reason,(uint64_t)0)
#define PANIC2(reason,extra) panic(__FILE__, __func__, _xstr(__LINE__), (reason), (extra))

void panic(const char *file, const char *func, const char *line, const char *reason, uint64_t extra);

#endif