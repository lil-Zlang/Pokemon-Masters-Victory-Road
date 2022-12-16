#ifndef _VECTOR2D_H
#define _VECTOR2D_H
#include <iostream>

class Vector2D {
public: 
	double x;
	double y;

	Vector2D(); // Default constructor
	Vector2D(double in_x, double in_y);

	friend Vector2D operator*(const Vector2D&v1, const double& d);
	friend Vector2D operator/(const Vector2D&v1, const double& d);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v1);
};

#endif /* Vector2D.h*/
