#pragma once
#ifndef TARGET_MOVEMENT_H
#define TARGET_MOVEMENT_H

#include "Helper_Header.h"
#include "Simulator.h"

using namespace std;

class Target_Movement_T
{
public:
	
	bool target_movement_test(std::string test, std::string Logs, std::string input,int stamp,char* argv[]) {
		
		bool test1 = false;
		int counter = 0;
		Simulator * sim = new Simulator();
		sim->start_simulator_T(test, Logs, input, argv);
		
		delete sim;
		return true;

	}

};
#endif