#pragma once

#ifndef SECTOR_H
#define SECTOR_H

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
		/****************** IS TARGET INSIDE SECTOR AREA ******************/
		bool isPointInsideArea(Dt3dPoint);

	public:
		/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
		Sector();
		~Sector();
		/****************** GETTERS /SETTERS ******************************/
		void setid(int id);
		void setA(Dt3dPoint*);
		void setB(Dt3dPoint*);
		void setC(Dt3dPoint*);
		Dt3dPoint* getA();
		Dt3dPoint* getB();
		Dt3dPoint* getC();
		int getid();
		std::string toString();
};

#endif

