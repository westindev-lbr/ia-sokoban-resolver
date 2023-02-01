#include <cstdio>
#include <SWI-cpp.h>

// swipl-ld -ld g++ -goal true 2.cpp 2-f.pl
// attention, recompile nécessaire si 2-f.pl change

int main(int _ac, char** _av) {
  PL_initialise(_ac, _av);
  
  PlTermv pl_args2(1);
  PlQuery q0("f", pl_args2);
  while( q0.next_solution()) {
    printf("---> %s\n", (char *)pl_args2[0]);
  }

  return 0;
}
