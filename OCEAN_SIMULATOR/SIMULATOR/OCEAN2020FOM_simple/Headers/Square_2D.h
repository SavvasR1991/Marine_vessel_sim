#pragma once
#ifndef SQUARE_2D_H
#define SQUARE_2D_H
#include "Point.h"

class Square_2d {

private:
	Point* A;
	Point* B;
	Point* C;
	Point* D;

public:
	Square_2d(Point* a, Point* b, Point* c, Point* d){
		A = new Point(a->x(), a->y(), 0.0);
		B = new Point(b->x(), b->y(), 0.0);
		C = new Point(c->x(), c->y(), 0.0);
		D = new Point(d->x(), d->y(), 0.0);
	}
	Square_2d(Point a, Point b, Point c, Point d) {
		A = new Point(a.x(), a.y(), 0.0);
		B = new Point(b.x(), b.y(), 0.0);
		C = new Point(c.x(), c.y(), 0.0);
		D = new Point(d.x(), d.y(), 0.0);
	}
	Point* getPointA() {  return A;}
	double getPointA_x() {	return A->x();}
	double getPointA_y() {	return A->y();}

	Point* getPointB() {  return B;}
	double getPointB_x() {	return B->x();}
	double getPointB_y() {	return B->y();}

	Point* getPointC() {  return C;}
	double getPointC_x() {	return C->x();}
	double getPointC_y() {	return C->y();}

	Point* getPointD() {  return D;}
	double getPointD_x() {  return D->x();}
	double getPointD_y() {  return D->y();}

	void print_square() {
		std::cout << "Square ABCD\n";
		std::cout << "  A = [" << A->x() << "," << A->y() << "]\n";
		std::cout << "  B = [" << B->x() << "," << B->y() << "]\n";
		std::cout << "  C = [" << C->x() << "," << C->y() << "]\n";
		std::cout << "  D = [" << D->x() << "," << D->y() << "]\n\n";
	}
};

#endif