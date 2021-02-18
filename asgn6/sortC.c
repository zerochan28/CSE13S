#include "sortC.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t move_c;
uint32_t compare_c;

// This part is translated and modified by the pseudocode from Professor Long
//
// Sorts by inserting the item to its correct location in array
// a : The array to sort.
// length : The length of the array.
//
void sort_C(uint32_t a[], uint32_t length) {
  for (uint32_t i = 1; i < length; i++) {
    uint32_t temp = a[i];
    move_c++;
    int j = i - 1;
    while (j >= 0 && a[j] > temp) {
      a[j + 1] = a[j];
      compare_c++;
      move_c++;
      j = j - 1;
    }
    // if loop breaks due to j < 0, we do not need to count as comparison
    if (j >= 0) {
      compare_c++;
    }
    a[j + 1] = temp;
    move_c++;
  }
  return;
}
