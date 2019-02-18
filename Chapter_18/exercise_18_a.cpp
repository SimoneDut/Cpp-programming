#include <cstdlib>
#include <iostream>

class A {
protected:
  int x;
public:
  A() : x(1) {}
  explicit A(int y) : x(y) {}
  int getx() { return x; }
};

class B: public A {
public:
  void someFunction() {
    x++;
  }
  // Would produce an error, due to the protected attribute of x
  // void someFunction(A* anA) {
  //   anA->x++;
  // }
  void someFunction(B* aB) {
    aB->x++;
  }
};

class C: public B {
  void anotherFunction() {
    x--;
  }
};

int main() {
  A a1(5);
  B b1;
  B b2;
  C c1;
  b1.someFunction();
  std::cout << "a1.x is " << a1.getx() << "\n";
  std::cout << "b1.x is " << b1.getx() << "\n";
  b1.someFunction(&b1);
  b1.someFunction(&b2);
  // it's not possible to assign &a1 to a pointer to B
  // b1.someFunction(&a1);
  std::cout << "now b1.x is " << b1.getx() << "\n";
  std::cout << "and b2.x is " << b2.getx() << "\n";
  c1.someFunction();
  std::cout << "c1.x is " << c1.getx() << "\n";
  // only A and its childrens' member functions can access x
  // c1.anotherFunction();
  // however it is possible to assign &c1 to a pointer to B
  b1.someFunction(&c1);
  std::cout << "now c1.x is " << c1.getx() << "\n";
  return EXIT_SUCCESS;
}
