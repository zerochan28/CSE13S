#include "bf.h"
#include "gs.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

extern FILE *yyin;
extern char *yytext;
extern int yylex(void);
extern int yylex_destroy(void);

bool move_to_front;

int main() {
  
  BloomFilter *bf = bf_create(10);
  
  if(bf == NULL) {
    exit(1);
  }

  yyin = fopen("read.txt", "r");
  char *oldspeak;
  char *newspeak;
  bool flip_old = false;
  GoodSpeak *sp;
  while (yylex()!=EOF) {
      if(!flip_old){
        oldspeak = yytext;
        //printf("%s",oldspeak);
        flip_old = true;
      } else {
        newspeak = yytext;
        //printf("%s\n",newspeak);
        sp = gs_create(oldspeak, newspeak);
        bf_insert(bf, oldspeak);
        flip_old = false;
        oldspeak = NULL;
        newspeak = NULL;
      }
  }
  yylex_destroy(); 
 // uint32_t length = pow(2, 20);

  bf_delete(bf);
  gs_delete(sp);
  bf = NULL;
  sp = NULL;
}
