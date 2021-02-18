#ifndef __GS_H__
#define __GS_H__

#include <stdio.h>

typedef struct GoodSpeak {
  char *old_speak;
  char *new_speak;
} GoodSpeak;

GoodSpeak *gs_create(char *old_speak, char *new_speak);

void gs_add(GoodSpeak *gs, char *new_speak);

void gs_delete(GoodSpeak *gs);

#endif
