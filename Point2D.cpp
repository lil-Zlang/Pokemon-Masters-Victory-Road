#include "Point2D.h"
#include <cmath>
#include <iostream>

using namespace std;

Point2D::Point2D() {
	x = 0.0; 
	y = 0.0;
}

Point2D::Point2D(double in_x, double in_y) {
	x = in_x;
	y = in_y;
}

std::ostream& operator<<(std::ostream& os, const Point2D& p1) {
	os << "(" << p1.x << ", " << p1.y << ")" ;
	return os;
}

Point2D operator+(Point2D& p1, Vector2D& v1) {
	return Point2D(p1.x + v1.x, p1.y + v1.y);
}

Vector2D operator-(Point2D & p1, Point2D & p2) {
	return Vector2D(p1.x - p2.x, p1.y - p2.y);
}
//non-member function
double GetDistanceBetween(Point2D p1, Point2D p2) {
	double x = p2.x - p1.x; 
	double y = p2.y - p1.y;
	return sqrt(x * x + y * y);
}



