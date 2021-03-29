#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>


namespace {

	
	double json_reader_data_test(std::string test, std::string sim, std::string sector) {
		const char * c = test.c_str();
		std::ifstream infile(c);
		std::string line;
		bool sim_found = false;
		double data = 0;
		while (std::getline(infile, line)) {
			if (line.find(sim) != std::string::npos) {
				sim_found = true;
			}
			if (sim_found) {
				if (line.find("}") != std::string::npos) {
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
			throw std::invalid_argument("No data exists. Terminate \n");
			system("pause");
			exit(-1);
		}
		return data;
	}

	std::string json_reader_data_test_description(std::string test_num, std::string path) {

		const char * c = test_num.c_str();
		std::ifstream infile(c);
		std::string line;
		bool sim_found = false;
		std::string  data ;

		while (std::getline(infile, line)) {

			if (line.find(path) != std::string::npos) {
				sim_found = true;
			}
			if (sim_found) {
				if (line.find("}") != std::string::npos) {
					cout << path << " " << line << endl;

					throw std::invalid_argument("No data exists. Read whole file. Terminate \n");
				}
				else {
					if (line.find("description") != std::string::npos) {
						unsigned first = line.find(": ");
						unsigned last = line.find(",");
						data = (line.substr(first + 2, last - first - 2));
						break;
					}
				}
			}
		}

		if (!sim_found) {
			throw std::invalid_argument("No data exists. Terminate \n");
			system("pause");
			exit(-1);
		}
		return data;
	}
	int json_reader_get_total_num(std::string test) {
		return int(json_reader_data_test(test, "Total_Tests", "Number"));
	}

	void json_reader_set_data(std::string category,std::string test, std::map<std::string, double> &data_input) {
		data_input.clear();
		const char * c = category.c_str();
		std::ifstream infile(c);
		std::string line;
		double data = 0;
		bool sim_found = false;
		std::map<std::string, double>::iterator it = data_input.begin();
		while (std::getline(infile, line)) {
			if (line.find(test) != std::string::npos) {
				sim_found = true;
				continue;
			}
			if (sim_found) {
				if (line.find("}") != std::string::npos) {
					break;
				}
				std::string attributte = line.substr(0, line.find(":")); // token is "scott"
				std::string value = line.substr(line.find(":"), line.find(",")); // token is "scott"

				value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
				value.erase(std::remove(value.begin(), value.end(), ','), value.end());
				value.erase(std::remove(value.begin(), value.end(), ':'), value.end());
				attributte.erase(std::remove(attributte.begin(), attributte.end(), ' '), attributte.end());
				attributte.erase(std::remove(attributte.begin(), attributte.end(), '\"'), attributte.end());
				data_input.insert(it, std::pair<std::string, double>(attributte, atof(value.c_str())));
			}
		}
	}

}