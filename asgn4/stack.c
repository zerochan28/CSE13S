#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(int capacity, char name) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  if (s == NULL) {
    exit(1);
  } else {
    s->name = name;
    s->top = 0;
    s->items = (int *)calloc(capacity, sizeof(int));
    if (s->items == NULL) {
      exit(1);
    } else {
      s->capacity = capacity;
      return s;
    }
  }
}

void stack_delete(Stack *s) {
  free(s->items);
  free(s);
  s = NULL;
}

int stack_pop(Stack *s) {
  if (stack_empty(s)) {
    exit(1);
  } else {
    int return_disk = s->items[s->top - 1];
    s->top--;
    return return_disk;
  }
}

void stack_push(Stack *s, int item) {
  if (s->top == s->capacity) {
    exit(1);
  } else {
    s->items[s->top] = item;
    s->top++;
  }
}

bool stack_empty(Stack *s) {
  if (s->top == 0) {
    return true;
  }
  return false;
}
