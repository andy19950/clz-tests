#include <stdlib.h>
#include <math.h>
#include "clz.h"

int clz_recur(uint32_t x, int size)
{
	if(size == 0) return 0; 
	// shift upper half down, rest is filled up with 0s 
	uint16_t upper = (x >> size); 
	// mask upper half away
	int loc = (int) ceil(log((double)size)/log((double)2));
	uint16_t lower = (x & TABLE[loc]);
	return upper ? clz_recur(upper, size/2) : size + clz_recur(lower, size/2);
}


int clz_itera(uint32_t x) {
    int n = 32, c = 16;
    do {
        uint32_t y = x >> c;
        if (y) { n -= c; x = y; }
        c >>= 1;
    } while (c);
    return (n - x);
}

uint32_t clz_Harley(uint32_t x)
{
    static const uint8_t Table[] = {
      0xFF, 0, 0xFF, 15, 0xFF, 1, 28, 0xFF,
      16, 0xFF, 0xFF, 0xFF, 2, 21, 29, 0xFF,
      0xFF, 0xFF, 19, 17, 10, 0xFF, 12, 0xFF,
      0xFF, 3, 0xFF, 6, 0xFF, 22, 30, 0xFF,
      14, 0xFF, 27, 0xFF, 0xFF, 0xFF, 20, 0xFF,
      18, 9, 11, 0xFF, 5, 0xFF, 0xFF, 13,
      26, 0xFF, 0xFF, 8, 0xFF, 4, 0xFF, 25,
      0xFF, 7, 24, 0xFF, 23, 0xFF, 31, 0xFF,
    };
/* Propagate leftmost 1-bit to the right */
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
 
    /* x = x * 0x6EB14F9 */
    x = (x << 3) - x;   /* Multiply by 7. */
    x = (x << 8) - x;   /* Multiply by 255. */
    x = (x << 8) - x;   /* Again. */
    x = (x << 8) - x;   /* Again. */

    return (Table[x >> 26]);
}

