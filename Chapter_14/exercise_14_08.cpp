#include <cstdio>
#include <cstdlib>

1class Point {
private:
  int x;
  int y;
public:
  void setLocation(int newX, int newY) {
    x = newX;
    y = newY;
  }
  int getX() const {
    return x;
  }
  int getY() const {
    return y;
  }
};

void printPoint(const char * name, const Point & p) {
  printf("%s: (%d,%d)\n", name, p.getX(), p.getY());
}

void f(Point & p) {
  printPoint("p",p);
  p.setLocation(p.getX()+2, p.getY()-1);
}

int main(void) {
  Point p1;
  Point p2;
  p1.setLocation(2, 4);
  p2.setLocation(3, 5);
  f(p1);
  f(p2);
  printPoint("p1",p1);
  printPoint("p2",p2);
  return EXIT_SUCCESS;
}
