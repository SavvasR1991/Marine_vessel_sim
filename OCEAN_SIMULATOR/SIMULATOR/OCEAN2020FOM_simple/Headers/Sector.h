#pragma once
#ifndef SECTOR_H
#define SECTOR_H

/******************************* SECTOR.CPP ***********************************/
// [1] Sector()													  constructor
// [2] ~Sector()								                  destructor, delete sector
// [3] float area(double, double, double, double, double, double) calculate distances
// [4] bool Sector::isPointInsideArea(Dt3dPoint)			      check if target is in sector's range
// [5] getters, setters
/******************************* SECTOR.CPP ***********************************/

#include <matrix/3dPoint.h>
#include <stdio.h>
#include <iostream>

class Sector
{
	private:
		/****************** SECTOR ATTRIBUTES *****************************/
		int id;
		Dt3dPoint* a;
		Dt3dPoint* b;
		Dt3dPoint* c;

	public:
		/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
		Sector() {}
		~Sector() {
			std::cout << "	 Sector " << this->id << " Deleted" << std::endl;
			delete a;
			delete b;
			delete c;
		}

		/******************************* GETTERS/SETTERS *****************************************/
		void setid(int id) { this->id = id; }
		int getid() { return this->id; }

		void setA(Dt3dPoint *a) { this->a = a; }
		void setB(Dt3dPoint *b) { this->b = b; }
		void setC(Dt3dPoint *c) { this->c = c; }

		Dt3dPoint* getA() { return this->a; }
		Dt3dPoint* getB() { return this->b; }
		Dt3dPoint* getC() { return this->c; }


		/************************ IS TARGET INSIDE SECTOR AREA ***********************************/
		float area(double x1, double y1, double x2, double y2, double x3, double y3)
		{
			return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
		}

		bool check_if_is_one_point()
		{
			if (getA()->x() == getB()->x()) {
				if (getA()->x() == getC()->x()) {
					if (getA()->y() == getB()->y()) {
						if (getA()->y() == getC()->y()) {
							return true;
						}
					}
				}
			}
			return false;
		}

		bool isPointInsideArea(Dt3dPoint checkPoint)
		{
			double x1, x2, x3, y1, y2, y3, x, y;
			x1 = this->a->x();
			y1 = this->a->y();
			x2 = this->b->x();
			y2 = this->b->y();
			x3 = this->c->x();
			y3 = this->c->y();
			x = checkPoint.x();
			y = checkPoint.y();

			/* Calculate area of triangle ABC */
			float A = area(x1, y1, x2, y2, x3, y3);
			/* Calculate area of triangle PBC */
			float A1 = area(x, y, x2, y2, x3, y3);
			/* Calculate area of triangle PAC */
			float A2 = area(x1, y1, x, y, x3, y3);
			/* Calculate area of triangle PAB */
			float A3 = area(x1, y1, x2, y2, x, y);
			/* Check if sum of A1, A2 and A3 is same as A */
			return (A == A1 + A2 + A3);
		}

		float sign(Dt3dPoint p1, Dt3dPoint p2, Dt3dPoint p3)
		{
			return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
		}

		bool PointInSector(Dt3dPoint pt)
		{

			float d1, d2, d3;
			bool has_neg, has_pos;

			d1 = sign(pt, *this->a, *this->b);
			d2 = sign(pt, *this->b, *this->c);
			d3 = sign(pt, *this->c, *this->a);

			has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
			has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

			return !(has_neg && has_pos);
		}
		/********************** RETURN SECTOR COORD TO STRING *********************************/
		std::string toString()
		{
			std::string point = std::to_string(this->c->x()) + " " + std::to_string(this->c->y()) + " " + std::to_string(this->c->z()) + " | " +
				std::to_string(this->b->x()) + " " + std::to_string(this->b->y()) + " " + std::to_string(this->b->z()) +" | " +
				std::to_string(this->a->x()) + " " + std::to_string(this->a->y()) + " " + std::to_string(this->a->z()) + "\n";
			return point;
		}


		int point_in_sector(double x, double y) {

		}

};

#endif

