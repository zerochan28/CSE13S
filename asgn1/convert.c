#include <stdio.h>

int main(void) {
  float TmpC, TmpK, TmpF, TmpRa, TmpD, TmpRe, TmpRo;
  int Min = 0, Max = 190, Inc = 10;
  printf("Celsius   Kelvin   Fahrenheit   Rankine");
  printf("   Delisle   Reaumur   Romer\n");
  printf("-------   ------   ----------   -------");
  printf("   -------   -------   -----\n");
  TmpC = Min;
  while (TmpC <= Max) {
    TmpK = TmpC + 273.15;
    TmpF = (9.00 / 5.00) * TmpC + 32;
    TmpRa = (9.00 / 5.00) * TmpC + 491.67;
    TmpD = (3.00 / 2.00) * (100 - TmpC);
    TmpRe = (4.00 / 5.00) * TmpC;
    TmpRo = (21.00 / 40.00) * TmpC + 7.5;
    printf("%7.2f %8.2f %12.2f %9.2f", TmpC, TmpK, TmpF, TmpRa);
    printf("%10.2f %9.2f %7.2f\n", TmpD, TmpRe, TmpRo);
    TmpC = TmpC + Inc;
  }
  return 0;
}
