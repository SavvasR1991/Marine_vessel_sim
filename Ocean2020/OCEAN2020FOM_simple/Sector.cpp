#include "Sector.h"

/******************************* SECTOR.CPP ***********************************/
// [1] Sector()													  constructor
// [2] ~Sector()								                  destructor, delete sector
// [3] float area(double, double, double, double, double, double) calculate distances
// [4] bool Sector::isPointInsideArea(Dt3dPoint)			      check if target is in sector's range
// [5] getters, setters
/******************************* SECTOR.CPP ***********************************/


/******************************* CONSTRUCTOR/DESTRUCTOR ***********************************/
Sector::Sector(){}
Sector::~Sector(){
	std::cout<<  "	 Sector "<<this->id<<" Deleted" << std::endl;
	delete a;
	delete b;
	delete c;
}

/******************************* GETTERS/SETTERS *****************************************/
void Sector::setid(int id) { this->id = id; }
int Sector::getid() { return this->id; }

void Sector::setA(Dt3dPoint *a) { this->a = a; }
void Sector::setB(Dt3dPoint *b) { this->b = b; }
void Sector::setC(Dt3dPoint *c) { this->c = c; }

Dt3dPoint* Sector::getA() { return this->a; }
Dt3dPoint* Sector::getB() { return this->b; }
Dt3dPoint* Sector::getC() { return this->c; }


/************************ IS TARGET INSIDE SECTOR AREA ***********************************/
float area(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

/* A function to check whether point P(x, y) lies inside the triangle formed
   by A(x1, y1), B(x2, y2) and C(x3, y3) */
bool Sector::isPointInsideArea(Dt3dPoint checkPoint)
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

/********************** RETURN SECTOR COORD TO STRING *********************************/
std::string Sector::toString()
{
	std::string point = std::to_string(this->c->x()) + " " + std::to_string(this->c->y()) +" | "+
						std::to_string(this->b->x()) + " " + std::to_string(this->b->y()) +" | "+
						std::to_string(this->a->x()) + " " + std::to_string(this->a->y()) +"\n";
	return point;
}
