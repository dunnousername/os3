#include <stdint.h>
#include <endian.h>

/* most of this file needs to be looked over/rewritten if we ever decide to work with middle endian */
#define INVALID_ENDIAN_CHECK(x) (((x) != ENDIAN_BIG) && ((x) != ENDIAN_LITTLE))

int convert8 (uint8_t  *w, int from, int to) {
    /* all endians are the same at the byte level */
    if (INVALID_ENDIAN_CHECK(from) || INVALID_ENDIAN_CHECK(to)) {
        return -1;
    }

    return 0;
}

int convert16(uint16_t *w, int from, int to) {
    if (INVALID_ENDIAN_CHECK(from) || INVALID_ENDIAN_CHECK(to)) {
        return -1;
    }

    if (from == to) {
        return 0;
    }

    if ((from == ENDIAN_LITTLE) && (to == ENDIAN_BIG)) {
        /* swapping is the same both ways */
        return convert16(w, to, from);
    }

    if ((to == ENDIAN_LITTLE) && (from == ENDIAN_BIG)) {
        uint8_t *b = (void *) w;
        uint8_t tmp;
        tmp  = b[0];
        b[0] = b[1];
        b[1] =  tmp;

        return 0;
    }
    
    return -1;
}

int convert32(uint32_t *w, int from, int to) {
    if (INVALID_ENDIAN_CHECK(from) || INVALID_ENDIAN_CHECK(to)) {
        return -1;
    }

    if (from == to) {
        return 0;
    }

    if ((from == ENDIAN_LITTLE) && (to == ENDIAN_BIG)) {
        /* swapping is the same both ways */
        return convert32(w, to, from);
    }

    if ((to == ENDIAN_LITTLE) && (from == ENDIAN_BIG)) {
        uint8_t *b = (void *) w;
        uint8_t tmp;
        tmp  = b[0];
        b[0] = b[3];
        b[3] =  tmp;
        tmp  = b[1];
        b[1] = b[2];
        b[2] =  tmp;

        return 0;
    }
    
    return -1;
}

int convert64(uint64_t *w, int from, int to) {
    if (INVALID_ENDIAN_CHECK(from) || INVALID_ENDIAN_CHECK(to)) {
        return -1;
    }

    if (from == to) {
        return 0;
    }

    if ((from == ENDIAN_LITTLE) && (to == ENDIAN_BIG)) {
        /* swapping is the same both ways */
        return convert64(w, to, from);
    }

    if ((to == ENDIAN_LITTLE) && (from == ENDIAN_BIG)) {
        uint8_t *b = (void *) w;
        uint8_t tmp;
        tmp  = b[0];
        b[0] = b[7];
        b[7] =  tmp;
        tmp  = b[1];
        b[1] = b[6];
        b[6] =  tmp;
        tmp  = b[2];
        b[2] = b[5];
        b[5] =  tmp;
        tmp  = b[3];
        b[3] = b[4];
        b[4] =  tmp;

        return 0;
    }
    
    return -1;
}