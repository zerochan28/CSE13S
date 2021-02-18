#include "sortA.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t move_a;
uint32_t compare_a;

// Most code of sort A comes from Professor Long
//
// Finds the index of element of least value in a bounded array
// a:       The array to search in.
// first:   The index of the first element to search from
// last:    The index of the last element to search to.
//
uint32_t min_index(uint32_t a[], uint32_t first, uint32_t last) {
  uint32_t smallest = first; // Assume the first is the least
  for (uint32_t i = first; i < last; i += 1) {
    smallest = a[i] < a[smallest] ? i : smallest;
    compare_a++;
  }
  return smallest;
}

//
// Sorts by repeatedly finding the element of least value
//
// a: The array to sort
// length: The length of array
//
void sort_A(uint32_t a[], uint32_t length) {
  for (uint32_t i = 0; i < length - 1; i += 1) {
    uint32_t smallest = min_index(a, i, length);
    if (smallest != i) {
      SWAP_a(a, smallest, i);
    }
  }
  return;
}

//
// SWAP two elements and counter add three due to three moves
// Move one element to temp, move y element to x position, put temp to y
//
void SWAP_a(uint32_t *array, uint32_t x, uint32_t y) {
  uint32_t temp = array[x];
  array[x] = array[y];
  array[y] = temp;
  move_a += 3;
  return;
}
