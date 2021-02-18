#include "sieve.h"
#include <math.h>
#include <stdio.h>

// This part of code comes from Assignment pdf created by Professor Long
// Idea of this part of code is using Sieve of Eratosthenes
void sieve(BitVector *v) {
  bv_set_all_bits(v); // Assume all are prime .
  bv_clr_bit(v, 0); // 0 is , well , zero .
  bv_clr_bit(v, 1); // 1 is unity .
  bv_set_bit(v, 2); // 2 is prime .
  for (uint32_t i = 2; i <= sqrtl(bv_get_len(v)); i += 1) {
    // Prime means bit is set.
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
        bv_clr_bit(v, (k + i) * i); // Its multiples are composite
      }
    }
  }
  return;
}
