#include "gs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gs_create
// Create a goodspeak
GoodSpeak *gs_create(char *old_speak, char *new_speak) {
  GoodSpeak *gs = calloc(1, sizeof(GoodSpeak));
  if (gs == NULL) {
    exit(1);
  }
  gs->old_speak = strdup(old_speak);
  if (new_speak) {
    gs->new_speak = strdup(new_speak);
  }
  return gs;
}

// gs_add
// add the new_speak for translation
void gs_add(GoodSpeak *gs, char *new_speak) {
  gs->new_speak = strdup(new_speak);
  return;
}

// gs_delete
// delete the goodspeak and free the memory
void gs_delete(GoodSpeak *gs) {
  if (gs != NULL) {
    free(gs->old_speak);
    gs->old_speak = NULL;
    if (gs->new_speak) {
      free(gs->new_speak);
      gs->new_speak = NULL;
    }
    free(gs);
    gs = NULL;
  }
  return;
}
