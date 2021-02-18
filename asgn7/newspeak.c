#include "bf.h"
#include "gs.h"
#include "hash.h"
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "sh:f:mb"
extern FILE *yyin;
extern char *yytext;
extern int yylex(void);
extern int yylex_destroy(void);
bool move_to_front;
uint32_t distance;
char *lower_case(char *tt);
double bf_density(BloomFilter *bf, uint32_t size);
double ht_avg_len(uint32_t size, uint32_t counter);
double bf_rate(uint32_t size, uint32_t counter);

int main(int argc, char *argv[]) {
  // Set some default value for the program
  // The default value of hash table is 10000
  // The default value of bloom filter is 2^20
  uint32_t bf_default = pow(2, 20);
  uint32_t ht_default = 10000;
  uint32_t bf_size = bf_default;
  uint32_t ht_size = ht_default;
  // Use two bool varaivles to check whether user choose these option
  bool stat = false;
  bool rule = false;
  // Print error if user gives wrong option
  if (argc == 1) {
    printf("You have to choose at least one option(-m -b)\n");
    return 0;
  }

  if (argc > 5) {
    printf("You probide too much option!\n");
    return 0;
  }

  int ch;
  while ((ch = getopt(argc, argv, OPTIONS)) != -1) {

    switch (ch) {
    case 's':
      stat = true;
      break;

    case 'h':
      ht_size = atoi(optarg);
      if (ht_size < 1 || ht_size == 0) {
        printf("The size of HashTable have to bigger than 1\n");
        return 0;
      }
      break;

    case 'f':
      bf_size = atoi(optarg);
      if (bf_size < 1 || bf_size == 0) {
        printf("The size of Bloom Filter have to bigger than 1\n");
        return 0;
      }
      break;

    case 'm':
      if (rule) {
        printf("You cannot supply -m -b at the same time!\n");
        return 0;
      }
      move_to_front = true;
      rule = true;
      break;

    case 'b':
      if (rule) {
        printf("You cannot supply -m -b at the same time!\n");
        return 0;
      }
      move_to_front = false;
      rule = true;
      break;

    default:
      printf("You can only supply -s -h -f -m -b\n");
      return 0;
    }
  }
  // If user did not choose rule
  // Set the default to no rule
  if (!rule) {
    move_to_front = false;
    return 0;
  }
  // Create a bloom filter and a hash table
  BloomFilter *bf = bf_create(bf_size);
  HashTable *ht = ht_create(ht_size);

  if (bf == NULL || ht == NULL) {
    exit(1);
  }

  // scan the badspeak.txt and store them into filter and hash table
  if ((yyin = fopen("badspeak.txt", "r")) == NULL) {
    printf("NULL document\n");
    exit(1);
  }
  // Use counter to calculate how many words are added
  uint32_t word_counter = 0;
  char *badspeak;
  while (yylex() != EOF) {
    badspeak = yytext;
    bf_insert(bf, badspeak);
    word_counter++;
    GoodSpeak *sp = gs_create(badspeak, NULL);
    ht_insert(ht, sp);
  }
  fclose(yyin);
  yylex_destroy();

  // scan the goodspeak.txt and store them into filter and hash table
  if ((yyin = fopen("goodspeak.txt", "r")) == NULL) {
    printf("NULL document\n");
    exit(1);
  }
  char *oldspeak;
  char *newspeak;
  // Use bool to flip the store of words
  // when the flip is false, store the word to filter and create a goodspeak
  // when the flip is true, store the new word to goodspeak and set to hash table
  bool flip_old = false;
  GoodSpeak *sp = NULL;
  while (yylex() != EOF) {
    if (!flip_old) {
      oldspeak = yytext;
      sp = gs_create(oldspeak, NULL);
      bf_insert(bf, oldspeak);
      flip_old = true;
    } else {
      newspeak = yytext;
      word_counter++;
      gs_add(sp, newspeak);
      ht_insert(ht, sp);
      flip_old = false;
      sp = NULL;
    }
  }
  fclose(yyin);
  yylex_destroy();

  char *badword = calloc(10000, sizeof(char));
  char *better = calloc(10000, sizeof(char));
  bool joycamp = false;
  bool revise = false;
  // search each word of user input from filter and hash table
  yyin = stdin;
  uint32_t search_counter = 0;

  while (yylex() != EOF) {
    char *test_text = yytext;
    test_text = lower_case(test_text);
    if (bf_probe(bf, test_text)) {
      ListNode *t = ht_lookup(ht, test_text);
      search_counter++;
      if (t != NULL) {
        if (((t->gs)->new_speak) == NULL) {
          if (!joycamp)
            joycamp = true;
          strcat(badword, test_text);
          strcat(badword, "\n");
        } else {
          strcat(better, (t->gs)->old_speak);
          strcat(better, "->");
          strcat(better, (t->gs)->new_speak);
          strcat(better, "\n");
          if (!revise)
            revise = true;
        }
      }
    }
  }
  fclose(yyin);
  yylex_destroy();

  // Print to output
  if (!stat && !joycamp && revise) {
    fprintf(stdout, "Dear Comrade,\n\n");
    fprintf(stdout,
        "Submitting your text helps to preserve feelings and prevent\n");
    fprintf(stdout,
        "badthink. Some of the words that you used are not goodspeak.\n");
    fprintf(stdout,
        "The list shows how to turn the oldspeak words into newspeak.\n\n");
    fprintf(stdout, "%s", better);
  }
  if (!stat && joycamp) {
    fprintf(stdout, "Dear Comrade,\n\n");
    fprintf(stdout,
        "You have chosen to use degenerate words that may cause hurt\n");
    fprintf(stdout,
        "feelings or cause your comrades to think unpleasant thoughts.\n");
    fprintf(stdout, "This is doubleplus bad. To correct your wrongthink and\n");
    fprintf(
        stdout, "save community consensus we will be sending you to joycamp\n");
    fprintf(stdout, "administered by Miniluv.\n");
    fprintf(stdout, "\nYour errors:\n\n");
    fprintf(stdout, "%s", badword);
    if (revise) {
      fprintf(stdout, "\nThink on these words during your vacation!\n\n");
      fprintf(stdout, "%s", better);
    }
  }

  // If user choose to print data
  if (stat) {
    fprintf(stdout, "Statistics\n");
    double density = bf_density(bf, bf_size);
    double ht_len = ht_avg_len(ht_size, word_counter);
    double false_rate = bf_rate(bf_size, word_counter);
    double d_distance = distance;
    double d_search_count = search_counter;
    double ave_dis = d_distance / d_search_count;
    fprintf(stdout, "Average Distance %.3f\n", ave_dis);
    fprintf(stdout, "Density of Bloom Filter is %.3f\n", density);
    fprintf(stdout, "Average Length of HashTable is %.3f\n", ht_len);
    fprintf(stdout, "The False Positive Rate is about %.3f\n", false_rate);
  }

  free(better);
  free(badword);
  better = NULL;
  badword = NULL;
  // delete the hash table and filter
  bf_delete(bf);
  ht_delete(ht);
  bf = NULL;
  ht = NULL;
  return 0;
}

// calculate the density of filter
// check how many bits is filled
// and return the density of bloom filter
double bf_density(BloomFilter *bf, uint32_t size) {
  double counter = 0;
  for (uint32_t i = 0; i < size; i++) {
    if (bv_get_bit(bf->filter, i)) {
      counter++;
    }
  }
  double d_size = size;
  return counter / d_size;
}

// calculate the average length of hash table
double ht_avg_len(uint32_t size, uint32_t counter) {
  double d_size = size;
  double d_counter = counter;
  double output = d_counter / d_size;
  return output;
}

// calculate the false positive rate by using formula
double bf_rate(uint32_t size, uint32_t counter) {
  double output;
  double d_size = size;
  double d_counter = counter;
  double rate = 1 - (1 / d_size);
  rate = pow(rate, 3 * d_counter);
  output = 1 - rate;
  output = pow(output, 3);
  return output;
}

// function to set mix case to lower case
char *lower_case(char *text) {
  uint32_t length = strlen(text);
  for (uint32_t i = 0; i < length; i++) {
    uint32_t as = text[i];
    if (as > 64) {
      if (as < 91) {
        *(text + i) = *(text + i) + 32;
      } else {
        *(text + i) = *(text + i);
      }
    } else {
      *(text + i) = *(text + i);
    }
  }
  return text;
}
