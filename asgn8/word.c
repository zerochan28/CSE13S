#include "word.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_ALPHA 256

// word_create
// allocate memory for word
// and return the pointer
Word *word_create(uint8_t *word, uint64_t length) {
  Word *w = calloc(1, sizeof(Word));
  if (w == NULL) {
    exit(1);
  } else {
    w->word_len = length;
    w->word = calloc(length, sizeof(uint8_t));
    if (w->word == NULL) {
      exit(1);
    }
    for (uint64_t i = 0; i < length; i++) {
      w->word[i] = word[i];
    }
    return w;
  }
}

// free the memory for word
void word_delete(Word *w) {
  if (w != NULL) {
    free(w->word);
    free(w);
    w = NULL;
    return;
  } else {
    return;
  }
}

// create the table by creating
// 0-255 entries by using ascii code
WordTable *wt_create(void) {
  WordTable *wt = calloc(1, sizeof(WordTable));
  if (wt == NULL) {
    exit(1);
  }
  uint8_t ascii_code = 0;
  for (uint16_t i = 0; i < NUM_ALPHA; i++) {
    uint8_t *ascii_w = { &ascii_code };
    wt->entries[i] = word_create(ascii_w, 1);
    ascii_code++;
  }
  return wt;
}

// reset table by deleting all previous entries
// and create new 0-255 entires by using ascii
void wt_reset(WordTable *wt) {
  for (uint64_t i = 0; i < UINT16_MAX; i++) {
    word_delete(wt->entries[i]);
    wt->entries[i] = NULL;
  }
  uint8_t ascii_code = 0;
  for (uint16_t i = 0; i < NUM_ALPHA; i++) {
    uint8_t *ascii_w = { &ascii_code };
    wt->entries[i] = word_create(ascii_w, 1);
    ascii_code++;
  }
}

// delete the word table by deleting
// all entries and free the memory for table
void wt_delete(WordTable *wt) {
  if (wt != NULL) {
    for (uint64_t i = 0; i < UINT16_MAX; i++) {
      word_delete(wt->entries[i]);
      wt->entries[i] = NULL;
    }
    free(wt);
    wt = NULL;
    return;
  } else {
    exit(1);
  }
}
