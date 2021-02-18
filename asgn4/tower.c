#include "stack.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "srn:"
int find_solution(int n, Stack *A, Stack *B, Stack *C);
void print_disk(int n, char origin, char destination);
void play_re(int n);
void play_st(int n);

// Read User input through getopt
// if the number of arguments is not followed the rules, show error
// command line argument should follow [-s] [-r] [-n] (number)
// check whether we need to print recursion or stack solution
// the default number of n is 5
// s_check: check whether use stacks mode
// r_cehck: check whether use recursion mode
int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("You must supply at least one option, [-s] [-r] [-n] (number)\n");
    return 0;
  }

  int ch;
  int n = 5;
  bool s_check = false;
  bool r_check = false;
  if (1 < argc && argc < 6) {
    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {

      switch (ch) {
      case 's':
        s_check = true;
        break;

      case 'r':
        r_check = true;
        break;

      case 'n':
        n = atoi(optarg);
        if (n == 0) {
          printf("You can supply number with -n, [-s] [-r] [-n] (number)\n");
          return 0;
        }
        break;

      default:
        printf(
            "You must supply at least one option, [-s] [-r] [-n] (number)\n");
        return 0;
      }
    }
  }

  if (argc > 5 && atoi(optarg) == 0) {
    printf("You can supply at most three options, [-s] [-r] [-n] (number)\n");
    return 0;
  }
  if (!(s_check || r_check)) {
    printf("You must supply at least one option for [-s] or [-r]\n");
    return 0;
  }
  // play stacks mode if need
  if (s_check) {
    play_st(n);
  }

  // play recursion mode if need
  if (r_check) {
    if (s_check)
      printf("\n");
    play_re(n);
  }

  return 0;
}

// print the format for recursion
// do recusion by using find_solution
// find_solution will return an int
// which is the steps of process of get the solution
void play_re(int n) {
  printf("================================\n");
  printf("--------   RECURSION   ---------\n");
  printf("================================\n");
  Stack *re_a = stack_create(n, 'A');
  Stack *re_b = stack_create(n, 'B');
  Stack *re_c = stack_create(n, 'C');

  // push disks to peg A from n to 1;
  for (int push_disk = n; push_disk > 0; push_disk--) {
    if (re_a == NULL) {
      exit(1);
    } else {
      stack_push(re_a, push_disk);
    }
  }
  int output = find_solution(n, re_a, re_b, re_c);
  printf("\nNumber of moves: %d\n", output);

  stack_delete(re_a);
  stack_delete(re_b);
  stack_delete(re_c);
}

// print the format for stacks
// this part of porgram will use iteration to achieve the goal
// we need to use the mode(n is even or odd); location of disk;
// and current disk is odd or even to decide what to do next
// a[n]: n-digit binary counter to run the program
// loc[n+1]: record the position of each disk
// mode: determine # of disk is a even number or odd number
// mark: record the # of current disk
void play_st(int n) {
  printf("================================\n");
  printf("----------   STACKS   ----------\n");
  printf("================================\n");
  Stack *peg_a = stack_create(n, 'A');
  Stack *peg_b = stack_create(n, 'B');
  Stack *peg_c = stack_create(n, 'C');

  // push all disks to peg A from disk n to disk 1
  for (int push_disk = n; push_disk > 0; push_disk--) {
    if (peg_a == NULL) {
      exit(1);
    } else {
      stack_push(peg_a, push_disk);
    }
  }
  int a[n];
  int loc[n + 1];
  loc[0] = 0;
  int p_t = pow(2, n);

  for (int c = 0; c < n; c++) {
    a[c] = 0;
    loc[c + 1] = 0;
  }
  int mode = n % 2;
  int mark = 0;

  for (int i = 1; i < p_t; i++) {
    // if last digit of binary counter is 0, then move disk 1
    // else move the disk which number is the location of last non-1 digit
    // e.g. current binary counter is 100111, then next step if 101000
    // in this situation, we should move disk 4
    if (a[n - 1] == 0) {
      a[n - 1]++;
      mark = 1;
    } else {
      int index = n - 2;
      bool test = true;
      while (test) {
        if (a[index] == 0) {
          for (int x = index; x < n; x++) {
            a[x] = 0;
          }
          a[index] = 1;
          mark = n - index;
          test = false;
        }
        index--;
      }
    }

    // move disk from current location to another peg
    // the direction of moving depends on two things
    // if total number of disks n is odd number (e.g. 7 disks)
    // for each odd disk (disk 1, 3, 5) they should move to right (A to B)
    // for each even disk (disk 2, 4, 6) they should move to left (A to C)
    // if total number of disks n is even numver (e.g. 6 disks)
    // for each odd disk (disk 1, 3, 5) they should move to left (A to C)
    // for each even disk (disk 2, 4, 6) they should move to right (A to B)
    int decide = (mark) % 2;
    if (decide == 0) {
      if (mode == 0) {
        if (loc[mark] == 0) {
          if (peg_a == NULL || peg_b == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_a);
            stack_push(peg_b, disk);
          }

          print_disk(mark, peg_a->name, peg_b->name);
          loc[mark] = 1;
        } else if (loc[mark] == 1) {
          if (peg_b == NULL || peg_c == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_b);
            stack_push(peg_c, disk);
          }

          print_disk(mark, peg_b->name, peg_c->name);
          loc[mark] = 2;
        } else {
          if (peg_c == NULL || peg_a == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_c);
            stack_push(peg_a, disk);
          }
          print_disk(mark, peg_c->name, peg_a->name);
          loc[mark] = 0;
        }

      } else {
        if (loc[mark] == 0) {
          if (peg_a == NULL || peg_c == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_a);
            stack_push(peg_c, disk);
          }
          print_disk(mark, peg_a->name, peg_c->name);
          loc[mark] = 2;
        } else if (loc[mark] == 1) {
          if (peg_b == NULL || peg_a == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_b);
            stack_push(peg_a, disk);
          }
          print_disk(mark, peg_b->name, peg_a->name);
          loc[mark] = 0;
        } else {
          if (peg_c == NULL || peg_b == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_c);
            stack_push(peg_b, disk);
          }
          print_disk(mark, peg_c->name, peg_b->name);
          loc[mark] = 1;
        }
      }
    } else {
      if (mode == 0) {
        if (loc[mark] == 0) {
          if (peg_a == NULL || peg_c == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_a);
            stack_push(peg_c, disk);
          }
          print_disk(mark, peg_a->name, peg_c->name);
          loc[mark] = 2;
        } else if (loc[mark] == 1) {
          if (peg_b == NULL || peg_a == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_b);
            stack_push(peg_a, disk);
          }
          print_disk(mark, peg_b->name, peg_a->name);
          loc[mark] = 0;
        } else {
          if (peg_c == NULL || peg_b == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_c);
            stack_push(peg_b, disk);
          }
          print_disk(mark, peg_c->name, peg_b->name);
          loc[mark] = 1;
        }
      } else {
        if (loc[mark] == 0) {
          if (peg_a == NULL || peg_b == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_a);
            stack_push(peg_b, disk);
          }

          print_disk(mark, peg_a->name, peg_b->name);
          loc[mark] = 1;
        } else if (loc[mark] == 1) {
          if (peg_b == NULL || peg_c == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_b);
            stack_push(peg_c, disk);
          }

          print_disk(mark, peg_b->name, peg_c->name);
          loc[mark] = 2;
        } else {
          if (peg_c == NULL || peg_a == NULL) {
            exit(1);
          } else {
            int disk = stack_pop(peg_c);
            stack_push(peg_a, disk);
          }
          print_disk(mark, peg_c->name, peg_a->name);
          loc[mark] = 0;
        }
      }
    }
  }
  printf("\nNumber of moves: %d\n", p_t - 1);
  stack_delete(peg_a);
  stack_delete(peg_b);
  stack_delete(peg_c);
}

// do recursion by recall itself
// The reason we flip peg B and C is because odd disks
// and even disks have different moving direction
// parameter A,B,C should be origin, destination, and temp peg
// result: count the number of steps
int find_solution(int n, Stack *A, Stack *B, Stack *C) {
  int result = 0;
  // when n euqals 1, then move disk 1 from current disk to another one
  if (n == 1) {
    if (A == NULL || B == NULL) {
      exit(1);
    } else {
      int disk = stack_pop(A);
      stack_push(B, disk);
    }
    char origin = A->name;
    char destination = B->name;
    print_disk(n, origin, destination);
    result++;
  } else {
    result = result + find_solution(n - 1, A, C, B);
    // move current disk n to destination peg
    if (A == NULL || B == NULL) {
      exit(1);
    } else {
      int disk = stack_pop(A);
      stack_push(B, disk);
    }
    char origin = A->name;
    char destination = B->name;
    print_disk(n, origin, destination);
    result++;
    result = result + find_solution(n - 1, C, B, A);
  }
  return result;
}

// print the process by using this function
// this function is shared by both solutions
void print_disk(int n, char origin, char destination) {
  printf("Move disk %d from peg %c to peg %c\n", n, origin, destination);
}
