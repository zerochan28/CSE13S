#include "trie.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_ALPHA 256

// create a new node by allocating memory
// and set the code for it
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *n = calloc(1, sizeof(TrieNode));
  if (n == NULL) {
    exit(1);
  }
  n->code = code;
  return n;
}

// free the memory allocated for node
// and set the pointer to NULL
void trie_node_delete(TrieNode *n) {
  if (n != NULL) {
    free(n);
    n = NULL;
    return;
  } else {
    exit(1);
  }
}

// Create trie by creating a root node
// and 0-255 children node
TrieNode *trie_create(void) {
  TrieNode *r = trie_node_create(0);
  for (uint16_t i = 0; i < NUM_ALPHA; i++) {
    r->children[i] = trie_node_create(i);
  }
  return r;
}

// reset the trie by kill all childrens
// and re-create the memory for 0-255
// children of root
void trie_reset(TrieNode *root) {
  for (int i = 0; i < NUM_ALPHA; i++) {
    trie_delete(root->children[i]);
    root->children[i] = trie_node_create(i);
  }
  return;
}

// delete the trie by kill all children
// and delete the root node
void trie_delete(TrieNode *n) {
  if (n != NULL) {
    for (uint16_t i = 0; i < NUM_ALPHA; i++) {
      trie_delete(n->children[i]);
    }
    trie_node_delete(n);
    n = NULL;
    return;
  } else {
    return;
  }
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  return n->children[sym];
}
