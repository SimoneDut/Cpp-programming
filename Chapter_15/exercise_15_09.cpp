#include <cstdio>
#include <cstdlib>

class IntArray {
public:
  int * elements;
  size_t numElements;
  IntArray(): elements(NULL), numElements(0) {}
  IntArray(size_t n): elements(new int[n]), numElements(n) {}
  ~IntArray() {
    delete[] elements;
  }
  IntArray(const IntArray & rhs): elements(new int[rhs.numElements]), numElements(rhs.numElements) {
    for (size_t i = 0; i < numElements; i++) {
      elements[i] = rhs.elements[i];
    }
  }
  IntArray & operator = (const IntArray & rhs) {
    if (this != &rhs) {
      int * temp = new int[rhs.numElements];
      for (size_t i = 0; i < rhs.numElements; i++) {
	temp[i] = rhs.elements[i];
      }
      delete[] elements;
      numElements = rhs.numElements;
      elements = temp;
    }
    return *this;
  }
  int & operator [] (size_t index) {
    return elements[index];
  }
  const int & operator [] (size_t index) const {
    return elements[index+1];
  }

  size_t size() const {
    return numElements;
  }
};

int main(void) {
  IntArray a;
  std::printf("size of a is %d\n",a.size());
  IntArray b(4);
  std::printf("size of b is %d\n",b.size());
  b.elements[1] = 1;
  b.elements[2] = 2;
  b.elements[3] = 3;
  b.elements[4] = 4;
  IntArray c = b;
  std::printf("size of c is %d\n",c.size());
  IntArray d;
  std::printf("size of d is %d\n",d.size());
  d = b;
  std::printf("now size of d is %d\n",d.size());
  std::printf("b[2] returns the value %d\n",b[2]);
  const IntArray e = b;
  std::printf("e[2] returns the value %d\n",e[2]);
  return EXIT_SUCCESS;
}
