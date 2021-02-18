#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
char *lower_case(char *text);

int main() {
  char *text = "ABCZaz!";
  char *newtext = lower_case(text);
  printf("%s\n",newtext);
}

char *lower_case(char *text) {
  uint32_t length = strlen(text);
  char *output = calloc(length,sizeof(char));
  //printf("length is %u",length);
  for(uint32_t i = 0; i < length; i++) {
    uint32_t as = text[i];
    //printf("ASC is %u",as);
    if(as > 64){
      if(as < 91){
        output[i] = tolower(text[i]);
      } else {
        output[i] = text[i];
      }
    } else {
      output[i] = text[i];
    }
  }
  return output;
}
