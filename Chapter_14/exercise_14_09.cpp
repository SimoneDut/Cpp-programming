#include <cstdio>
#include <cstdlib>
#include <cassert>

class Square {
private:
  double length;
public:
  void setEdgeLength(double edgeLength) {
    assert(edgeLength>=0);
    length = edgeLength;
  }
  double getEdgeLength() const {
    return length;
  }
  double getArea() const {
    return length*length;
  }
  double getPerimeter() const {
    return 4*length;
  }
};

int main(void) {
  Square squares[4];
  for (int i = 0; i < 4; i++) {
    squares[i].setEdgeLength(2*i+2);
  }
  for (int i = 0; i < 4; i++) {
    printf("Square %d has edge length %f\n", i, squares[i].getEdgeLength());
    printf("   and area %f\n", squares[i].getArea());
    printf("   and perimeter %f\n", squares[i].getPerimeter());
  }
  printf("Trying to set a negative edge length (should abort)\n");
  squares[0].setEdgeLength(-1);
  return EXIT_FAILURE;
}

