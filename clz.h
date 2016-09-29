#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define SIZE 16

static const uint16_t TABLE[] = {0x01, 0x03, 0x0f, 0xff, 0xffff};

int clz_recur(uint32_t x, int size);

int clz_itera(uint32_t x);

uint32_t clz_Harley(uint32_t x);
