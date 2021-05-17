#ifndef _ENDIAN_H_
#define _ENDIAN_H_

#include <stdint.h>

#define PLATFORM_NUMBITS __INTPTR_WIDTH__ 

#define ENDIAN_LITTLE 1
#define ENDIAN_BIG    2
/* #define ENDIAN_PDP    3 */

#ifndef ENDIAN_HOST
    #ifdef __BYTE_ORDER__
        #if   __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            #define ENDIAN_HOST ENDIAN_LITTLE
        #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
            #define ENDIAN_HOST ENDIAN_BIG
        #elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
            /* #define ENDIAN_HOST ENDIAN_PDP */
            #error "PDP middle-endian not supported"
        #else
            #error "endian not supported"
        #endif
    #else
        #error "__BYTE_ORDER__ undefined"
    #endif
#endif

int convert8 (uint8_t  *w, int from, int to);
int convert16(uint16_t *w, int from, int to);
int convert32(uint32_t *w, int from, int to);
int convert64(uint64_t *w, int from, int to);

#endif