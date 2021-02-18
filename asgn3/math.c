#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
long double Sin(long double x);
long double Cos(long double x);
long double Tan(long double x);
long double Exp(long double x);
#define OPTIONS "sctea"

int main(int argc, char *argv[]) {
  int ch;
  long double PI = M_PI;
  bool check_all = false; //Use the check if we need to print all
  // Check if User enter more than one command or enter nothing
  // the program will provides instruction if things happen
  if (argc == 1) {
    printf("You must supply the option, -s, -c, -t, -e or -a!\n");
    return 0;
  }
  if (argc > 2) {
    printf("You can only supply one command!\n");
    return 0;
  }
  while ((ch = getopt(argc, argv, OPTIONS)) != -1) {

    switch (ch) {

    // Set check_all to true and the program will start print with sin
    case 'a':
      check_all = true;

    // By using the loop, start with -2 pi and ends on 2 pi with step of pi/16
    // if check_all is true, the program will not break; else it will break
    case 's':
      printf("x         Sin             Library          Difference\n");
      printf("-         ---             -------          ----------\n");

      for (long double x = ((-2) * PI); x <= (2 * PI); x += (PI / 16)) {
        printf("%7.4Lf", x);
        long double sin_cal = Sin(x);
        printf("  %11.8Lf     ", sin_cal);
        long double sin_lib;
        sin_lib = sin(x);
        printf("%11.8Lf", sin_lib);
        printf("      %13.10Lf\n", sin_cal - sin_lib);
      }
      if (check_all) {
      } else {
        break;
      }

    // By using the loop, start with -2 pi and ends on 2pi with step of pi/16
    // if check_all is true, it will print specific format for better looks
    // and it will not break at the end; else it will break after printing
    case 'c':
      if (check_all) {
        printf("\n");
      }
      printf("x         Cos             Library          Difference\n");
      printf("-         ---             -------          ----------\n");

      for (long double x = ((-2) * PI); x <= (2 * PI); x += (PI / 16)) {
        printf("%7.4Lf", x);
        long double cos_cal = Cos(x);
        printf("  %11.8Lf     ", cos_cal);
        long double cos_lib;
        cos_lib = cos(x);
        printf("%11.8Lf", cos_lib);
        printf("      %13.10Lf\n", cos_cal - cos_lib);
      }
      if (check_all) {
      } else {
        break;
      }

    // By using loop, start with -(pi/2 - 0.001) and ends on (pi/2 - 0.001)
    // with step of pi/16
    // if check_all is true, it will print specific format for better looks
    // and it will not break at the end; else it will break after printing
    case 't':
      if (check_all) {
        printf("\n");
      }
      printf("x         Tan             Library          Difference\n");
      printf("-         ---             -------          ----------\n");

      for (long double x = -(PI / 2 - 0.001); x < (PI / 2 - 0.001);
           x += (PI / 16)) {
        printf("%7.4Lf", x);
        long double tan_cal = Tan(x);
        if (tan_cal < -100) {
          printf("  %13.8Lf ", tan_cal);
        } else {
          printf("  %11.8Lf ", tan_cal);
        }
        long double tan_lib;
        tan_lib = tan(x);

        // Using if and else to arrange the format for better look
        // due to the length of some value are different
        if (tan_lib < -100) {
          printf("  %13.8Lf", tan_lib);
        } else {
          printf("    %11.8Lf  ", tan_lib);
        }
        printf("    %13.10Lf\n", tan_cal - tan_lib);
      }
      if (check_all) {
      } else {
        break;
      }

    // by using loop, start with 0.0 and enes on 10.0 with step of 0.1
    // if check_all is true, it will print specific format for better looks
    case 'e':
      if (check_all) {
        printf("\n");
      }
      printf("x         e^x             Library          Difference\n");
      printf("-         ---             -------          ----------\n");
      for (long double x = 0.0; x < 10.0 + 0.001; x += 0.10) {
        long double exp_cal = Exp(x);
        long double exp_lib = exp(x);
        // Using if and else for arrange the format of printing
        // due to the length of some outputs are different
        if (exp_cal < 10) {
          printf("%6.4Lf    %10.8Lf      %10.8Lf      %13.10Lf\n", x, exp_cal,
              exp_lib, exp_cal - exp_lib);
        } else if (exp_cal < 100) {
          printf("%6.4Lf    %11.8Lf     %11.8Lf     %13.10Lf\n", x, exp_cal,
              exp_lib, exp_cal - exp_lib);
        } else if (exp_cal < 1000) {
          printf("%6.4Lf    %12.8Lf    %12.8Lf    %13.10Lf\n", x, exp_cal,
              exp_lib, exp_cal - exp_lib);
        } else if (exp_cal < 10000) {
          printf("%6.4Lf    %13.8Lf   %13.8Lf   %13.10Lf\n", x, exp_cal,
              exp_lib, exp_cal - exp_lib);
        } else if (exp_cal < 20000) {
          printf("%6.4Lf    %14.8Lf  %14.8Lf  %13.10Lf\n", x, exp_cal, exp_lib,
              exp_cal - exp_lib);
        } else if (exp_cal < 100000) {
          printf("%7.4Lf   %14.8Lf  %14.8Lf  %13.10Lf\n", x, exp_cal, exp_lib,
              exp_cal - exp_lib);
        }
      }
      break;

    default:
      printf("Please enter a valid command: -s, -c, -t, -e or -a!\n");
    }
  }
  return 0;
}

// Using Pade Approximation for sin
// by using the parameter x and calculate sin(x) and return
//
// Thr formula to calculate sin(x) is originated from Professor Long in piazza
long double Sin(long double x) {

  long double sin_output;

  long double n
      = x
        * (133684890792694976170345029120000.0
              + x * x
                    * (-20494411297105391300731453977600.0
                          + x * x
                                * (828214724158018950289951814400.0
                                      + x * x
                                            * (-13571254880131693253451022080.0
                                                  + x * x
                                                        * (104761946712028505958458400.0
                                                              + x * x
                                                                    * (-385435322571107751366060.0
                                                                          + x * x
                                                                                * 555846146649952654679.0))))));

  long double d
      = 133684890792694976170345029120000.0
        + x * x
              * (1786403835010438060992717542400.0
                    + x * x
                          * (11907940053967159035862828800.0
                                + x * x
                                      * (51483089628027222496531200.0
                                            + x * x
                                                  * (155112126388519498117920.0
                                                        + x * x
                                                              * (315769438704063484140.0
                                                                    + x * x
                                                                          * 348811434161499491.0)))));

  sin_output = n / d;
  return sin_output;
}

// Using Pade Apporximation for cos
// by using parameter x to calculate cos(x) and return
//
// The formula to calculate cos(x) is originated from Professor Long in Piazza
long double Cos(long double x) {

  long double cos_output;

  long double n
      = 5678043342594608587418174133135360000.0
        + x * x
              * (-2766947970816677844675767800512000000.0
                    + x * x
                          * (201009028104053320861704991168972800.0
                                + x * x
                                      * (-5111523211284970219456401196512000.0
                                            + x * x
                                                  * (58952154443929839057881771856000.0
                                                        + x * x
                                                              * (-338938990285362196790251245600.0
                                                                    + x * x
                                                                          * (957049523024893733365255920.0
                                                                                - 1073709653319163169669575.0
                                                                                      * x
                                                                                      * x))))));

  long double d
      = 5678043342594608587418174133135360000.0
        + x * x
              * (72073700480626449033319266055680000.0
                    + x * x
                          * (460739069591187569274035316172800.0
                                + x * x
                                      * (1946779310366782428666671942400.0
                                            + x * x
                                                  * (5956981238166831424568016000.0
                                                        + x * x
                                                              * (13425143673825939828558240.0
                                                                    + x * x
                                                                          * (21053833464601381951920.0
                                                                                + 18164636218281257111.0
                                                                                      * x
                                                                                      * x))))));

  cos_output = n / d;
  return cos_output;
}

// tan(x) = sin(x) / cos(x)
// by using parameter x simply call sin(x) and cos(x) and return the value
long double Tan(long double x) {
  long double sin_result = Sin(x);
  long double cos_result = Cos(x);
  long double tan_output = sin_result / cos_result;
  return tan_output;
}

// Using Taylor series to calculate exponent
// this program will use 45 terms to calculate
// by using the parameter x to calculate and return the value
// this part will use for loop to add each term
long double Exp(long double x) {
  long double exp_output = 1;
  for (int ex = 1; ex <= 45; ex++) {
    long double exp_up = 1;
    long double exp_low = 1;
    for (int loop = 1; loop <= ex; loop++) {
      exp_up = exp_up * x;
      exp_low = exp_low * loop;
    }
    exp_output = exp_output + exp_up / exp_low;
  }
  return exp_output;
}
