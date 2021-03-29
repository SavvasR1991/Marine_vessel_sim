#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

// Class to represent points.
class Point {
private:
	double xval, yval, zval;
public:
	// Constructor uses default arguments to allow calling with zero, one,
	// or two values.
	Point(double x = 0.0, double y = 0.0, double z = 0.0) {
		xval = x;
		yval = y;
		zval = z;

	}
	// Extractors.
	double x() { return xval; }
	double y() { return yval; }
	double z() { return zval; }

	void set_x(double x) { this->xval = x; }
	void set_y(double y) { this->yval = y; }
	void set_z(double z) { this->zval = z; }

	// Distance to another point.  Pythagorean thm.
	double dist(Point other) {
		double xd = xval - other.xval;
		double yd = yval - other.yval;
		return sqrt(xd*xd + yd * yd);
	}

	// Add or subtract two points.
	Point add(Point b)
	{
		return Point(xval + b.xval, yval + b.yval);
	}
	Point sub(Point b)
	{
		return Point(xval - b.xval, yval - b.yval);
	}

	// Move the existing point.
	void move(double a, double b)
	{
		xval += a;
		yval += b;
	}

	// Print the point on the stream.  The class ostream is a base class
	// for output streams of various types.
	void print(ostream &strm)
	{
		strm << "(" << xval << "," << yval << ")";
	}
};

#endif