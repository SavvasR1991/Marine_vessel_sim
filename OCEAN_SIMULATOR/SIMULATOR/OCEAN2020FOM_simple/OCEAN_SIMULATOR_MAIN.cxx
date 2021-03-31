/****************************************************************************
 * Copyright (c) 2020 VT MAK. Ocean Vessel simulator
 * All rights reserved.
 * Author: Rostantis Savvas
 ****************************************************************************/

#include "Simulator.h"
#include "Tests\run_tests.h"

//************ SELECT EXECUTION_MODE = "OCEAN_PROJECT", FOR START SIMULATOR ************//
//************ SELECT EXECUTION_MODE = "TEST", FOR TESTING *****************************//

constexpr auto EXECUTION_MODE = "OCEAN_PROJECT";
constexpr auto UNIVERSITY_TAG = "NKUA";
constexpr auto SCENARIO = "1";

int main(int argc, char* argv[])
{
	print_color_message("------------ " + std::string(UNIVERSITY_TAG) + " ------------\n\n", COLOR_TEXT::GRAY_COLOR);
	if (std::string(EXECUTION_MODE) == "OCEAN_PROJECT") {
		std::cout << "---> OPERATION OCEAN_PROJECT MODE <--- \n\n";
		Simulator* simulator = new Simulator();
		try {
			simulator->start_simulator(argc, argv, std::string(UNIVERSITY_TAG), std::string(SCENARIO));
		}
		DtCATCH_AND_WARN(std::cout);
		delete simulator;
		system("pause");
		return 0;
	}
	else if (std::string(EXECUTION_MODE) == "TEST") {
		std::cout << "---> OPERATION TEST MODE <---\n\n";
		Run_tests *simulator_test = new Run_tests(argc, argv);
		try {
			simulator_test->execute_all_tests();
		}
		DtCATCH_AND_WARN(std::cout);
		delete simulator_test;
		system("pause");
		return 0;
	}
	else {
		std::cout << "No valid mode was entered... Exit..\n\n";
		system("pause");
		return -1;
	}
}