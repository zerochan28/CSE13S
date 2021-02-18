#include "ll.h"
#include "gs.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool move_to_front;
uint32_t distance;
ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *n = calloc(1, sizeof(ListNode));
  if (n == NULL) {
    return NIL;
  }
  n->gs = gs;
  n->next = NULL;
  return n;
}

// delete the node and delete the next one unitll no next one
void ll_node_delete(ListNode *n) {
  if (n != NULL) {
    ListNode *r = n->next;
    gs_delete(n->gs);
    free(n);
    n = NULL;
    ll_node_delete(r);
    r = NULL;
  }
  return;
}

// delete the whole linked list by delete all nodes
void ll_delete(ListNode *head) {
  ll_node_delete(head);
  return;
}

// Create a new node and insert to head
ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  ListNode *n = ll_node_create(gs);
  if (n != NULL) {
    n->next = *head;
    return n;
  }
  return NIL;
}

// Use for loop to search
// If find the same key, return the node
// If not, search next node
// If current node is NULL, return
ListNode *ll_lookup(ListNode **head, char *key) {
  ListNode *n = *head;
  ListNode *p = NULL;
  char *os;
  while (n != NULL) {
    os = (n->gs)->old_speak;
    distance++;
    if (strncmp(os, key, 255) == 0) {
      break;
    } else {
      p = n;
      n = n->next;
    }
  }
  if (move_to_front && p) {
    p->next = n->next;
    n->next = *head;
    *head = n;
  }
  os = NULL;
  return n;
}
