#include <cstdio>
#include <cstdlib>
#include <cassert>

class Point {
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
  Point operator + (const Point & rhs) const {
    Point ans;
    ans.x = x + rhs.x;
    ans.y = y + rhs.y;
    return ans;
  }
  Point operator - (const Point & rhs) const {
    Point ans;
    ans.x = x - rhs.x;
    ans.y = y - rhs.y;
    return ans;
  }
  Point operator * (const int & rhs) const {
    Point ans;
    ans.x = x * rhs;
    ans.y = y * rhs;
    return ans;
  }
  Point operator / (const int & rhs) const {
    assert(rhs != 0);
    Point ans;
    ans.x = x / rhs;
    ans.y = y / rhs;
    return ans;
  }
  Point & operator += (const Point & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  Point & operator -= (const Point & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  Point & operator *= (const int & rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }
  Point & operator /= (const int & rhs) {
    assert(rhs != 0);
    x /= rhs;
    y /= rhs;
    return *this;
  }
  bool operator == (const Point & rhs) {
    if (x != rhs.x) { return false; }
    if (y != rhs.y) { return false; }
    return true;
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
  int a;
  p1.setLocation(2, 4);
  p2.setLocation(3, 5);
  printPoint("p1",p1);
  printPoint("p2",p2);
  printPoint("p1 + p2",p1+p2);
  printPoint("p1 - p2",p1-p2);
  a = 1;
  printPoint("p1 * 1",p1*a);
  a = 2;
  printPoint("p1 * 2",p1*a);
  a = 3;
  printPoint("p1 * 3",p1*a);
  a = 0;
  printPoint("p1 * 0",p1*a);
  a = 1;
  printPoint("p1 / 1",p1/a);
  a = 2;
  printPoint("p1 / 2",p1/a);
  a = 3;
  printPoint("p1 / 3",p1/a);
  if (p1 == p2) { printf("p1 == p2 is true\n"); }
  else { printf("p1 == p2 is false\n"); }
  if (p2 == p1) { printf("p2 == p1 is true\n"); }
  else { printf("p2 == p1 is false\n"); }
  if (p1 == p1) { printf("p1 == p1 is true\n"); }
  else { printf("p1 == p1 is false\n"); }
  if (p2 == p2) { printf("p2 == p2 is true\n"); }
  else { printf("p2 == p2 is false\n"); }
  printPoint("p1 += p2",p1+=p2);
  printPoint("p1 -= p2",p1-=p2);
  a = 5;
  printPoint("p1 *= 5",p1*=a);
  printPoint("p1 /= 5",p1/=a);
  printf("Test assert\n");
  printPoint("p1 /= 0",p1/=0);
  return EXIT_SUCCESS;
}
