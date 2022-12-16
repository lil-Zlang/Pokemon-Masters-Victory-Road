#ifndef _POINT2D_H
#define _POINT2D_H

#include "Vector2D.h"
#include <iostream>

class Point2D {
public: 
	double x;
	double y;

	Point2D();
	Point2D(double in_x, double in_y);
	
	friend std::ostream& operator<<(std::ostream& os, const Point2D& p1);
	friend Point2D operator+(Point2D& p1, Vector2D& v1);
	friend Vector2D operator-(Point2D& p1, Point2D& p2);
};

double GetDistanceBetween(Point2D p1, Point2D p2);

#endif