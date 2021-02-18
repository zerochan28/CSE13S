#ifndef _SORT_A_H_
#define _SORT_A_H_

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern uint32_t move_a;
extern uint32_t compare_a;

uint32_t min_index(uint32_t a[], uint32_t first, uint32_t last);

void sort_A(uint32_t a[], uint32_t length);

void SWAP_a(uint32_t *array, uint32_t x, uint32_t y);

#endif
