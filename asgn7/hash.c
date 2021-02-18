#include "hash.h"
#include "gs.h"
#include "ll.h"
#include "speck.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
//
// Constructor for a HashTable.
//
// length : Length of the HashTable .
// salt : Salt for the HashTable .
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return NULL;
}
// Free memory of hash table
// Free all memory for linked list
void ht_delete(HashTable *ht) {
  if (ht != NULL) {
    for (uint32_t i = 0; i < ht->length; i++) {
      ll_delete(ht->heads[i]);
      ht->heads[i] = NULL;
    }
    free(ht->heads);
    free(ht);
    ht = NULL;
  }
  return;
}

// Use salt to get a hash value
// Test whether the word exist on that linked list
ListNode *ht_lookup(HashTable *ht, char *key) {
  uint32_t hash_f = hash(ht->salt, key) % (ht->length);
  return ll_lookup((ht->heads) + hash_f, key);
}

// Use salt to get a hash value
// Insert the goodspek to linked list
void ht_insert(HashTable *ht, GoodSpeak *gs) {
  uint32_t hash_f = hash(ht->salt, gs->old_speak) % (ht->length);
  ListNode *n = ll_insert((ht->heads) + hash_f, gs);
  ht->heads[hash_f] = n;
  n = NULL;
  return;
}
