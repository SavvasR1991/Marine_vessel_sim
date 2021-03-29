#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>

namespace {

	double json_reader_data(std::string sim, std::string sector, std::string file) {
		std::ifstream infile(file);
		std::string line;

		bool sim_found = false;
		double data = 0;
		while (std::getline(infile, line)) {
			if (line.find(sim) != std::string::npos) {
				sim_found = true;
			}
			if (sim_found) {
				if (line.find("}") != std::string::npos) {
					cout << "-- No data " << sector << " exists.exeption \n";

					throw std::invalid_argument("No data exists. Read whole file. Terminate \n");
				}
				else {
					if (line.find(sector) != std::string::npos) {
						unsigned first = line.find(": ");
						unsigned last = line.find(",");
						data = std::stod(line.substr(first + 2, last - first - 2));
						break;
					}
				}
			}
		}
		if (!sim_found) {
			data = 0;
			cout<<"-- No data " <<sector << " exists. Data set to zero \n";
		}
		return data;
	}

	std::string json_reader_data_description(std::string sim, std::string file) {
		std::ifstream infile(file);
		std::string line;

		bool sim_found = false;
		std::string data;
		while (std::getline(infile, line)) {
			if (line.find(sim) != std::string::npos) {
				sim_found = true;
			}
			if (sim_found) {
				if (line.find("}") != std::string::npos) {
					throw std::invalid_argument("No data exists. Read whole file. Terminate \n");
				}
				else {
					if (line.find("Description") != std::string::npos) {
						unsigned first = line.find(": ");
						unsigned last = line.find(",");
						data = (line.substr(first + 3, last - first - 4));
						break;
					}
				}
			}
		}
		if (!sim_found) {
			throw std::invalid_argument("No data exists. Terminate \n");
		}
		return data;
	}

}