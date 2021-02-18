#include "bf.h"
#include "speck.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7; // U.S. Consitution
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3; // Il nome della rosa
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0; // The Cremation of Sam McGee
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}
// Free the memory for Bloom Filter
void bf_delete(BloomFilter *bf) {
  if (bf != NULL) {
    bv_delete(bf->filter);
    free(bf);
    bf = NULL;
  }
  return;
}

// Call three hash functions and get the hash value
// Set bits on corresponding location
void bf_insert(BloomFilter *bf, char *key) {
  uint32_t bv_len = bv_get_len(bf->filter);
  uint32_t hash_f = hash(bf->primary, key) % bv_len;
  uint32_t hash_s = hash(bf->secondary, key) % bv_len;
  uint32_t hash_t = hash(bf->tertiary, key) % bv_len;
  bv_set_bit(bf->filter, hash_f);
  bv_set_bit(bf->filter, hash_s);
  bv_set_bit(bf->filter, hash_t);
  return;
}
// Call three hash functions and get hash values
// Test whether corresponding bit is filled by 1
bool bf_probe(BloomFilter *bf, char *key) {
  uint32_t bv_len = bv_get_len(bf->filter);
  uint32_t hash_f = hash(bf->primary, key) % bv_len;
  uint32_t hash_s = hash(bf->secondary, key) % bv_len;
  uint32_t hash_t = hash(bf->tertiary, key) % bv_len;
  uint8_t bit_f = bv_get_bit(bf->filter, hash_f);
  uint8_t bit_s = bv_get_bit(bf->filter, hash_s);
  uint8_t bit_t = bv_get_bit(bf->filter, hash_t);
  if (bit_f && bit_s && bit_t) {
    return true;
  } else {
    return false;
  }
}
