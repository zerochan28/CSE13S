#include "sortB.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t move_b;
uint32_t compare_b;

// This part is translated from pseudocode provided by Professor Long
//
// Sorts by comparing adjacent paris of items.
//
// a : The array to sort
// length : The length of the array;
//
void sort_B(uint32_t a[], uint32_t length) {
  bool swapped = true;
  for (uint32_t i = length - 1; swapped && 0 < i; i--) {
    swapped = false;
    for (uint32_t o = 0; o <= i - 1; o++) {
      compare_b++;
      if (a[o] > a[o + 1]) {
        SWAP_b(a, o, o + 1);
        swapped = true;
      }
    }
  }
  return;
}

// SWAP two elements and counter should add three due to have three moves
// Move x element to temp, move y to x position, and move temp to y
void SWAP_b(uint32_t *array, uint32_t x, uint32_t y) {
  uint32_t temp = array[x];
  array[x] = array[y];
  array[y] = temp;
  move_b += 3;
  return;
}
