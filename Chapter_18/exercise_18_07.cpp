#include <iostream>
#include <cstdlib>

class A {
protected:
  int x;
public:
  A() : x(0) { std::cout << "A()\n"; }
  A(int _x) : x(_x) { std::cout << "A(" << x << ")\n"; }
  virtual ~A()  { std::cout << "~A()\n"; }
  int myNum() const { return x; }
  virtual void setNum(int n) { x = n; }
};

class B : public A {
protected:
  int y;
public:
  B() : y(0) { std::cout << "B()\n"; }
  B(int _x, int _y) : A(_x), y(_y) { std::cout << "B(" << x << "," << y << ")\n"; }
  virtual ~B()  { std::cout << "~B()\n"; }
  virtual int myNum() const { return y; }
  virtual void setNum(int n) { y = n; }
};

int main(void) {
  B* b1 = new B();
  B* b2 = new B(3,8);
  A* a1 = b1;
  A* a2 = b2;
  b1->setNum(99);
  a1->setNum(42);
  std::cout << "a1->myNum() = " << a1->myNum() << "\n";
  std::cout << "a2->myNum() = " << a2->myNum() << "\n";
  std::cout << "b1->myNum() = " << b1->myNum() << "\n";
  std::cout << "b2->myNum() = " << b2->myNum() << "\n";
  delete b1;
  delete a2;
  return EXIT_SUCCESS;
}
