#include <cstdio>
#include <cstdlib>

class Example {
private:
  int data;
public:
  Example(): data(0) {
    std::printf("Example default constructor\n");
  }
  Example(int x): data(x) {
    std::printf("Example constructor (%d)\n",data);
  }
  Example(const Example & e) : data(e.data) {
    printf("Example copy constructor (%d)\n",data);;
  }
  Example & operator = (const Example & rhs) {
    data = rhs.data;
    printf("Example assign operator\n");
    return *this;
  }
  ~Example() {
    printf("Example destructor [with %d]\n",data);
  }
  void add(int x) {
    data += x;
  }
};

void f(Example & a, Example b) {
  printf("Inside f\n");
  a.add(10);
  b.add(20);
}

int main(void) {
  printf("e1:\n");
  Example e1;
  printf("e2:\n");
  Example e2(4);
  printf("e3:\n");
  Example e3 = e2;
  e3.add(5);
  printf("e1 = e2:\n");
  e1 = e2;
  printf("f(e1,e2):\n");
  f(e1,e2);
  printf("back in main\n");
  return EXIT_SUCCESS;
}
