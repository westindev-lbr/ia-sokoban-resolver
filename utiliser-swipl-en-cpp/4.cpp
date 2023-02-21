#include <cstdio>
#include <SWI-cpp.h>

// swipl-ld -ld g++ -goal true 4.cpp empty.pl

int main(int _ac, char** _av) {
  printf("using fac.pl to compute 10!\n");
  PL_initialise(_ac, _av);

  PlTermv pl_args(1);
  pl_args[0] = "fac.pl";
  PlCall("consult", pl_args);

  PlTermv pl_args2(2);
  pl_args2[0] = 10;
  PlQuery q0("fac", pl_args2);
  while( q0.next_solution()) {
    printf("---> %d\n", (int)pl_args2[1]);
  }

  return 0;
}
