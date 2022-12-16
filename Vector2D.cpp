#include "Vector2D.h"
#include <iostream>

using namespace std;

Vector2D::Vector2D() {
	x = 0.0;
	y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y) {
	x = in_x;
	y = in_y;
}

Vector2D operator*(const Vector2D& v1, const double& d) {
	return Vector2D(v1.x * d, v1.y * d);
}

Vector2D operator/(const Vector2D& v1, const double& d) {
	return Vector2D(v1.x / d, v1.y / d);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v1) {
	os << "<" << v1.x << ", " << v1.y << ">";
	return os;
}
