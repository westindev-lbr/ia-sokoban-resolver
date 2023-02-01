#include <cstdio>
#include <SWI-cpp.h>

// swipl-ld -ld g++ -goal true 3.cpp empty.pl
// on retire 3-f.pl de la compile pour le charger à chq execution
// charger empty.pl (qui est vide) permet de ne pas avoir le message de bienvenu de Prolog

int main(int _ac, char** _av) {
  PL_initialise(_ac, _av);

  PlTermv pl_args(1);
  pl_args[0] = "3-f.pl";
  PlCall("consult", pl_args);

  PlTermv pl_args2(1);
  PlQuery q0("f", pl_args2);
  while( q0.next_solution()) {
    printf("---> %s\n", (char *)pl_args2[0]);
  }

  return 0;
}
