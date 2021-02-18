#ifndef _SORT_B_H_
#define _SORT_B_H_

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern uint32_t move_b;
extern uint32_t compare_b;

void sort_B(uint32_t a[], uint32_t length);

void SWAP_b(uint32_t *array, uint32_t x, uint32_t y);

#endif
