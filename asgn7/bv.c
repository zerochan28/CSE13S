#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  if (v == NULL) {
    exit(1);
  } else {
    int length_bv = (bit_len / 8) + 1;
    v->length = bit_len;
    v->vector = (uint8_t *)calloc(length_bv, sizeof(uint8_t));
    if (v->vector == NULL) {
      exit(1);
    } else {
      return v;
    }
  }
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  v = NULL;
}

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  return v->length;
}

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  uint32_t set_block = i / 8;
  uint32_t set_index = i % 8;
  v->vector[set_block] |= (0x01 << set_index);
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  uint32_t clr_block = i / 8;
  uint32_t clr_index = i % 8;
  v->vector[clr_block] &= ~(0x01 << clr_index);
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint32_t get_block = i / 8;
  uint32_t get_index = i % 8;
  uint8_t temp = v->vector[get_block];
  for (uint32_t o = 1; o <= get_index; o++) {
    temp = (temp) / 2;
  }
  return temp % 2;
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  for (uint32_t o = 0; o <= v->length; o++) {
    bv_set_bit(v, o);
  }
}
