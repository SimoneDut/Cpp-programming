#include <cstdlib>
#include <iostream>

class A {
public:
  A() { say("Hi",""); }
  ~A()  { say("Bye",""); }
  explicit A(const char* mesg) { say("Hi",mesg); }
  virtual void say(const char* mesg1, const char* mesg2) {
    std::cout << mesg1 << " from class A " << mesg2 << "\n";
  }
};

class B: public A {
public:
  B() { say("Hi",""); }
  ~B()  { say("Bye",""); }
  explicit B(const char* mesg) : A(mesg) { say("Hi",mesg); }
  virtual void say(const char* mesg1, const char* mesg2) {
    std::cout << mesg1 << " from class B " << mesg2 << "\n";
  }
};

int main() {
  A anA_1;
  B aB_1;
  A anA_2("anA_2");
  B aB_2("aB_2");
  A* ptr1 = &anA_1;
  A* ptr2 = &aB_1;
  return EXIT_SUCCESS;
}
