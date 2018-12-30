#include <cstdio>
#include <cstdlib>

void f(int & y, int * z) {
  printf("y = %d, *z = %d\n", y, *z);
  y += *z;
  *z = 42;
}

int main(void) {
  int a = 3;
  int b = 4;
  int &x = a;
  x = b;
  printf("a = %d, b = %d, x = %d\n", a, b, x);
  f(b, &x);
  printf("a = %d, b = %d, x = %d\n", a, b, x);
  return EXIT_SUCCESS;  
}
