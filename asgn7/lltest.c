#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "speck.h"
#include "gs.h"
#include "hash.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *A[9] = { "Ryan", "Simon", "Shitman", "Zero", "Chai", "Chen", "Wu",
    "Jin", "Slug" };
  char *B[9] = { "Ray", "Say", "BullShit", "Ling", "Jie", "Linhao", "Shilong",
    "Gold", "XJ" };
  uint32_t length = pow(2, 20);
  BloomFilter *bf = bf_create(length);
  GoodSpeak *bd = gs_create(A[4], B[4]);
  HashTable *ht = ht_create(2);
  bf_insert(bf, A[4]);
  bf_insert(bf, B[8]);
  ht_insert(ht, bd);
  bd = gs_create(B[8],A[8]);
  ht_insert(ht,bd);
  bd = gs_create(B[7],A[7]);
  ht_insert(ht, bd);
  ListNode *t = ht->heads[1];
  t = t->next;
  printf("%s\n",(t->gs)->new_speak);
  ListNode *n;
  if (bf_probe(bf, A[4])) {
    printf("Prob");
    n = ht_lookup(ht, A[4]);
    if (n == NULL) {
      printf("NULL\n");
      return 0;
    }
    printf("%s\n", (n->gs)->new_speak);
  }

  if (bf_probe(bf, B[8])) {
    printf("Prob");
    n = ht_lookup(ht, B[8]);
    if (n == NULL) {
      printf("NULL\n");
      return 0;
    }
    printf("%s\n", (n->gs)->new_speak);
  }

  if (!bf_probe(bf, A[8])) {
  printf("Nope\n");
  }
  bf_delete(bf);
  ht_delete(ht);
  free(ht);
  ht = NULL;
  free(bd);
  bd = NULL;
  return 0;
}
