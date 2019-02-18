#include <cstdlib>
#include <iostream>

class Point {
  double x;
  double y;
public:
  Point() : x(0.0), y(0.0) {}
  Point(const double initialX, const double initialY) : x(initialX), y(initialY) {}
  void setX(const double newX) { x = newX; }
  void setY(const double newY) { y = newY; }
  double getX() const { return x; }
  double getY() const { return y; }
};

class Shape {
public:
  virtual bool containsPoint(const Point& p) const = 0;
  virtual double getArea() const = 0;
  // Important, to dynamically dispatch the destructor
  virtual ~Shape() {}
};

class Rectangle : public Shape {
  Point lowerLeftCorner;
  double width;
  double height;
public:
  Rectangle() : lowerLeftCorner(Point(0.0,0.0)), width(0.0), height(0.0) {}
  Rectangle(const Point& initialLowerLeftCorner, const double initialWidth, const double initialHeight) : lowerLeftCorner(initialLowerLeftCorner),
													  width(initialWidth),
													  height(initialHeight) {}
  void setLowerLeftCorner(const Point& newLowerLeftCorner) { lowerLeftCorner = newLowerLeftCorner; }
  void setWidth(const double newWidth) { width = newWidth; }
  void setHeight(const double newHeight) { height = newHeight; }
  Point getLowerLeftCorner() { return lowerLeftCorner; }
  double getWidth() { return width; }
  double getHeight() { return height; }
  virtual bool containsPoint(const Point& p) const {
    bool ans;
    std::cout << "Rectangle with lowerLeftCorner (" << lowerLeftCorner.getX() << "," << lowerLeftCorner.getY()
	      << "), width " << width << ", and height " << height;
    if ((p.getX()>=lowerLeftCorner.getX())&&(p.getY()>=lowerLeftCorner.getY())
	&&(p.getX()<=(lowerLeftCorner.getX()+width))&&(p.getY()<=(lowerLeftCorner.getY()+height))) {
      std::cout << " contains ";
      ans = true;
    }
    else {
      std::cout << " does not contain ";
      ans = false;
    }
    std::cout << "point p (" << p.getX() << "," << p.getY() << ")\n";
    return ans;
  }
  virtual double getArea() const {
    double ans = width*height;
    std::cout << "Rectangle with lowerLeftCorner (" << lowerLeftCorner.getX() << "," << lowerLeftCorner.getY()
	      << "), width " << width << ", and height " << height << " has area " << ans << "\n";   
    return ans;
  }
};

#define PI 3.1415926535
class Circle : public Shape {
  Point center;
  double radius;
public:
  Circle() : center(Point(0.0,0.0)), radius(0.0) {}
  Circle(const Point& initialCenter, const double initialRadius) : center(initialCenter),
								   radius(initialRadius) {}

  void setCenter(const Point& newCenter) { center = newCenter; }
  void setradius(const double newRadius) { radius = newRadius; }
  Point getCenter() { return center; }
  double getradius() { return radius; }
  virtual bool containsPoint(const Point& p) const {
    bool ans;
    std::cout << "Circle with center (" << center.getX() << "," << center.getY()
	      << "), and radius " << radius;
    if (((p.getX()-center.getX())*(p.getX()-center.getX())+(p.getY()-center.getY())*(p.getY()-center.getY()))<=radius*radius) {
      std::cout << " contains ";
      ans = true;
    }
    else {
      std::cout << " does not contain ";
      ans = false;
    }
    std::cout << "point p (" << p.getX() << "," << p.getY() << ")\n";
    return ans;
  }
  virtual double getArea() const {
    double ans = radius*radius*PI;
    std::cout << "Circle with center (" << center.getX() << "," << center.getY()
	      << "), and radius " << radius << " has area " << ans << "\n";   
    return ans;
  }
};

int main() {
  Point p1;
  Point p2(3.0,4.0);
  Point p3(1.0,2.0);
  Rectangle rect1(p1,3.0,2.0);
  rect1.getArea();
  rect1.containsPoint(p1);
  rect1.containsPoint(p2);
  rect1.containsPoint(p3);
  Point p4(3.0,6.0);
  Point p5(4.0,5.0);
  Point p6(4.0,6.0);
  Point p7(5.0,6.0);
  Point p8(4.0,7.0);
  Circle circ1(p3,5.0);
  circ1.getArea();
  circ1.containsPoint(p4);
  circ1.containsPoint(p5);
  circ1.containsPoint(p6);
  circ1.containsPoint(p7);
  circ1.containsPoint(p8);
  return EXIT_SUCCESS;
}
