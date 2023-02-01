#include <cstdio>
#include <SWI-Prolog.h>

// après avoir installé swi-prolog (et peut être aussi swi-prolog-devel)
// pour pouvoir appeler Prolog à partir du C/C++
// https://www.swi-prolog.org/pldoc/man?section=calling-prolog-from-c

// pour avoir les paramètres
// pkg-config swipl --cflags
// pkg-config swipl --libs

// et selon les paramètres précédents, pour compiler
// g++ 1.cpp -I /opt/local/lib/swipl/include -L/opt/local/lib/swipl/lib/arm64-darwin -lswipl

int main(int _ac, char** _av) {
  PL_initialise(_ac, _av);
  printf("ok\n");
  return 0;
}
