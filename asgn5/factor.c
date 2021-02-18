#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "n:"
void prime_factor(int i);

// Main Function
// Use getopt and CommandLine to determine whether user provides correct command
// If user command cannot fulfill the requirement, then provide instruction
int main(int argc, char *argv[]) {
  uint32_t n = 0;
  int ch;
  // If User have not provide parameter, then set default to 100000
  if (argc == 1) {
    n = 100000;
  }
  if (argc == 2) {
    printf("You can supply -n option, factor [-n] (number)\n");
    return 0;
  }
  // If User provides -n (number), then set maximum to number n
  if (argc == 3) {
    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {

      switch (ch) {
      case 'n':
        n = atoi(optarg);
        if (n == 0) {
          printf("You can supply number with -n, factor [-n] (number)\n");
          return 0;
        }
      }
    }
  }

  if (argc > 3) {
    printf("You can only supply -n option, factor [-n] (number)\n");
    return 0;
  }
  // Crate bit vector and use sieve to determine prime and composite number
  BitVector *v = bv_create(n);
  sieve(v);
  // Run a for loop to print all numbers
  for (uint32_t i = 2; i <= n; i++) {
    // Get the value of bit
    // If return 1, then it is a prime number
    // If return 0, then it will be composite number
    uint8_t value = bv_get_bit(v, i);
    printf("%d ", i);
    // For prime number, simply print number and indicates it is 'P'
    // For compsoite number, we should print number and indictaes it is 'C'
    // Also, by calling function prime_factor, it will do prime factorization
    if (value == 1) {
      printf("P\n");
    } else {
      printf("C:");
      prime_factor(i);
      printf("\n");
    }
  }
  // Free memoery for bit vectors
  bv_delete(v);
  return 0;
}

// Prime_factorization
// find the smallest factor of i except 1
// do same operation again by using devide factor
// until no factors found.
// The reason to find the smallest factor
// is because the factor we got must be
// prime number which  does not have fator
// excpet 1 and itself.
void prime_factor(int i) {
  bool print_check = false;
  for (int o = 2; o <= i; o++) {
    if (i % o == 0) {
      printf(" %d", o);
      print_check = true;
      i = i / o;
      break;
    }
  }
  if (1 == i) {
    return;
  } else {
    if (print_check) {
      prime_factor(i);
    }
  }
}
