gcc -Wall -g -Iinclude -c src/vector.c -o build/vector.o
src/vector.c: In function ‘vector_get’:
src/vector.c:36:1: warning: control reaches end of non-void function [-Wreturn-type]
   36 | }
      | ^
gcc -Wall -g -Iinclude tests/vector_test.c build/vector.o -o build/vector_test -lm
tests/vector_test.c: In function ‘approx_equal’:
tests/vector_test.c:8:10: warning: implicit declaration of function ‘fabs’ [-Wimplicit-function-declaration]
    8 |   return fabs(a - b) < epsilon;
      |          ^~~~
tests/vector_test.c:5:1: note: include ‘<math.h>’ or provide a declaration of ‘fabs’
    4 | #include "../include/vector.h"
  +++ |+#include <math.h>
    5 |
tests/vector_test.c:8:10: warning: incompatible implicit declaration of built-in function ‘fabs’ [-Wbuiltin-declaration-mismatch]
    8 |   return fabs(a - b) < epsilon;
      |          ^~~~
tests/vector_test.c:8:10: note: include ‘<math.h>’ or provide a declaration of ‘fabs’
