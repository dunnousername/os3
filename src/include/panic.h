#ifndef _PANIC_H_
#define _PANIC_H_

#define _xstr(s) _str(s)
#define str(s) #s
#define PANIC(reason) panic(__FILE__, __func__, xstr(__LINE__), (reason))

void panic(char *file, char *func, char *line, char *reason);

#endif