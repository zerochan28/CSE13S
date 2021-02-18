#include "sortD.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_GAPS 8
uint32_t move_d;
uint32_t compare_d;

// This part is translated and modified by a pseudocode from Professor Long
//
// Sorts by sorting a pair of elements which far from a specific gap
//
// a : The array t sort.
// length: The length of the array.
//
void sort_D(uint32_t a[], uint32_t length) {
  uint32_t gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
  uint32_t j;
  uint32_t i;
  uint32_t o;
  for (o = 0; o < NUM_GAPS; o++) {
    uint32_t gap = gaps[o];
    for (i = gap; i < length; i++) {
      uint32_t temp = a[i];
      move_d++;
      for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
        a[j] = a[j - gap];
        move_d++;
        compare_d++;
      }
      // if the loops breaaks due to j < gap, we do not think we do a comparison
      if (j >= gap) {
        compare_d++;
      }
      a[j] = temp;
      move_d++;
    }
  }
  return;
}
