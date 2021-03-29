#pragma once
#ifndef SQUARE_3D_H
#define SQUARE_3D_H
#include "Point.h"


class Square_3d {

private:
	Point* A;
	Point* B;
	Point* C;
	Point* D;
	Point* E;
	Point* F;
	Point* G;
	Point* H;

public:
	Square_3d(Point* a, Point* b, Point* c, Point* d, Point* e, Point* f, Point* g, Point* h) {
		A = new Point(a->x(), a->y(), a->z());
		B = new Point(b->x(), b->y(), b->z());
		C = new Point(c->x(), c->y(), c->z());
		D = new Point(d->x(), d->y(), d->z());
		E = new Point(e->x(), e->y(), e->z());
		F = new Point(f->x(), f->y(), f->z());
		G = new Point(g->x(), g->y(), g->z());
		H = new Point(h->x(), h->y(), h->z());
	}
	Square_3d(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h) {
		A = new Point(a.x(), a.y(), a.z());
		B = new Point(b.x(), b.y(), b.z());
		C = new Point(c.x(), c.y(), c.z());
		D = new Point(d.x(), d.y(), d.z());
		E = new Point(e.x(), e.y(), e.z());
		F = new Point(f.x(), f.y(), f.z());
		G = new Point(g.x(), g.y(), g.z());
		H = new Point(h.x(), h.y(), h.z());
	}
	Point* getPointA() { return A; }
	double getPointA_x() { return A->x(); }
	double getPointA_y() { return A->y(); }
	double getPointA_z() { return A->z(); }

	Point* getPointB() { return B; }
	double getPointB_x() { return B->x(); }
	double getPointB_y() { return B->y(); }
	double getPointB_z() { return B->z(); }

	Point* getPointC() { return C; }
	double getPointC_x() { return C->x(); }
	double getPointC_y() { return C->y(); }
	double getPointC_z() { return C->z(); }

	Point* getPointD() { return D; }
	double getPointD_x() { return D->x(); }
	double getPointD_y() { return D->y(); }
	double getPointD_z() { return D->z(); }

	Point* getPointE() { return E; }
	double getPointE_x() { return E->x(); }
	double getPointE_y() { return E->y(); }
	double getPointE_z() { return E->z(); }

	Point* getPointF() { return F; }
	double getPointF_x() { return F->x(); }
	double getPointF_y() { return F->y(); }
	double getPointF_z() { return F->z(); }

	Point* getPointG() { return G; }
	double getPointG_x() { return G->x(); }
	double getPointG_y() { return G->y(); }
	double getPointG_z() { return G->z(); }

	Point* getPointH() { return H; }
	double getPointH_x() { return H->x(); }
	double getPointH_y() { return H->y(); }
	double getPointH_z() { return H->z(); }

	void print_square() {
		std::cout << "Square 3d ABCDEFGH\n";
		std::cout << "  A = [" << A->x() << "," << A->y() << "," << A->z() << "]\n";
		std::cout << "  B = [" << B->x() << "," << B->y() << "," << B->z() << "]\n";
		std::cout << "  C = [" << C->x() << "," << C->y() << "," << C->z() << "]\n";
		std::cout << "  D = [" << D->x() << "," << D->y() << "," << D->z() << "]\n";
		std::cout << "  E = [" << E->x() << "," << E->y() << "," << E->z() << "]\n";
		std::cout << "  F = [" << F->x() << "," << F->y() << "," << F->z() << "]\n";
		std::cout << "  G = [" << G->x() << "," << G->y() << "," << G->z() << "]\n";
		std::cout << "  H = [" << H->x() << "," << H->y() << "," << H->z() << "]\n\n";
	}
};

#endif