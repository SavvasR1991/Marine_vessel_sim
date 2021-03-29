#pragma once
#ifndef RUN_TEST_H
#define RUN_TEST_H

#include <Windows.h>
#include <chrono>
#include <string>

#include "Helper_Header.h"
#include "Collision_Avoidance_test.h"
#include "Possition_Prediction_test.h"
#include "Water_Waves_Kinematics_test.h"
#include "Test_Target_movement.h"
#include "Json_Reader.h"


class Run_tests {

private:

	int argc;
	char** argv;
	struct data {
		std::string description;
		std::string status;
	};
	Collision_Avoidance *detector_c;
	Predictor_Position *detector_p;
	Water_Waves_Kinematics *detector_w;
	FOM_EVENT *event;
	std::string Logs_Path;
	std::string Logs_Path_2;
	std::string logs_current_summary;
	std::vector<data> Test_status_water_waves;
	std::vector<data> Test_status_water_waves_sub;
	std::vector<data> Test_status_collision;
	std::vector<data> Test_status_prediction;
	std::vector<data> Test_status_movement;

	void set_up_unit_test() {
		this->detector_c = new Collision_Avoidance();
		this->detector_p = new Predictor_Position();
		this->detector_w = new Water_Waves_Kinematics(11,11,11);
		this->event = new FOM_EVENT("TEST");

	};

	void execute_collision_avoidance_test() {
		Collision_Avoidance_T test;
		std::map<std::string, double> data;
		std::string Test_Category = ExePath_t() +"\\Tests\\Input_Data_Collision_test.json";
		int total_tests = json_reader_get_total_num(Test_Category), i, passed = 0, failed = 0;
		bool result;

		print_color_message_t("\n-------- COLLISION AVOIDANCE TESTS TOTAL: " + to_string(total_tests) + " --------\n", 6);
		for (i = 1; i <= total_tests; i++) {
			json_reader_set_data(Test_Category, "Test_" + to_string(i), data); 
			result = test.collision_avoidance_test(data, this->Logs_Path, i, detector_c);
			std::string test_description = (json_reader_data_test_description(Test_Category, "Test_" + to_string(i)));
			print_color_message_t("----(" + to_string(i) + ")", 14);
			if (result) {
				passed++;
				Test_status_collision.push_back({ test_description,"PASSED" });
				print_color_message_t("TEST PASSED\n", 10);
			}
			else {
				failed++; 
				Test_status_collision.push_back({ test_description,"FAILED" });
				print_color_message_t("TEST FAILED\n", 12);
			}
		}

		if (passed != 0) { print_color_message_t("\n- PASSED TESTS:     " + to_string(passed) + "\n", 10); }
		if (failed != 0) { print_color_message_t("\n- FAILED TESTS:     " + to_string(failed) + "\n", 12); }
		print_color_message_t("- PASSED TESTS PER: " + to_string((double)(100.0 * passed) / (double)total_tests) + " %\n\n", 14);
	};
	
	void execute_possition_prediction_test() {
		Predictor_Position_T test;
		std::map<std::string, double> data;
		std::string Test_Category = ExePath_t() +"\\Tests\\Input_Data_Possition_Prediction_test.json";
		int total_tests = json_reader_get_total_num(Test_Category), i, passed = 0, failed = 0;
		bool result;

		print_color_message_t("\n-------- POSITION PREDICTION TESTS TOTAL: " + to_string(total_tests) + " --------\n", 6);
		for (i = 1; i <= total_tests; i++) {
			json_reader_set_data(Test_Category, "Test_" + to_string(i), data); 
			result = test.possition_avoidance_test(data, this->Logs_Path, i, detector_p);
			std::string test_description = (json_reader_data_test_description(Test_Category, "Test_" + to_string(i)));
			print_color_message_t("----(" + to_string(i) + ")", 14);
			if (result) {
				passed++;
				Test_status_prediction.push_back({ test_description,"PASSED" });
				print_color_message_t("TEST PASSED\n", 10);
			}
			else {
				failed++; 
				Test_status_prediction.push_back({ test_description,"FAILED" });
				print_color_message_t("TEST FAILED\n", 12);
			}
		}

		if (passed != 0) { print_color_message_t("\n- PASSED TESTS:     " + to_string(passed) + "\n", 10); }
		if (failed != 0) { print_color_message_t("\n- FAILED TESTS:     " + to_string(failed) + "\n", 12); }
		print_color_message_t("- PASSED TESTS PER: " + to_string((double)(100.0 * passed) / (double)total_tests) + " %\n\n", 14);
	};

	void execute_water_kinematis_test() {
		Water_Waves_Kinematics_T test;
		std::map<std::string, double> data;
		std::string Test_Category = ExePath_t() + "\\Tests\\Input_Data_Water_Waves_Kinematics_test.json";
		int total_tests = json_reader_get_total_num(Test_Category), i,passed = 0, failed = 0;
		bool result;

		print_color_message_t("\n-------- WATER WAVES KINEMATICS TESTS TOTAL: " + to_string(total_tests) + " --------\n", 6);
		for (i = 1; i <= total_tests; i++) {
			json_reader_set_data(Test_Category, "Test_" + to_string(i), data);
			result = test.water_waves_kinematics_test_1(data, this->Logs_Path, i, detector_w, this->event);
			std::string test_description = (json_reader_data_test_description(Test_Category, "Test_" + to_string(i)));
			print_color_message_t("----(" + to_string(i) + ")", 14);
			if (result) {
				passed++;
				Test_status_water_waves.push_back({test_description,"PASSED"} );
				print_color_message_t("TEST PASSED\n", 10);
			}
			else {
				failed++;
				Test_status_water_waves.push_back({test_description,"FAILED"} );
				print_color_message_t("TEST FAILED\n", 12);
			}
		}
		if (passed != 0) {	print_color_message_t("\n- PASSED TESTS:     " + to_string(passed) + "\n", 10);	}
		if (failed != 0) {	print_color_message_t("\n- FAILED TESTS:     " + to_string(failed) + "\n", 12);	}
		print_color_message_t("- PASSED TESTS PER: " + to_string((double)(100.0 * passed) / (double)total_tests) + " %\n\n", 14);



		std::map<std::string, double> data2;
		Test_Category = ExePath_t() + "\\Tests\\Input_Data_Water_Waves_Kinematics_test_Sub.json";
		total_tests = json_reader_get_total_num(Test_Category);
		passed = 0;
		failed = 0;

		print_color_message_t("\n-------- WATER WAVES KINEMATICS TESTS SUBWATER TOTAL: " + to_string(total_tests) + " --------\n", 6);
		for (i = 1; i <= total_tests; i++) {
			json_reader_set_data(Test_Category, "Test_" + to_string(i), data2);
			result = test.water_waves_kinematics_test_2(data2, this->Logs_Path_2, i, detector_w, this->event);
			std::string test_description = (json_reader_data_test_description(Test_Category, "Test_" + to_string(i)));
			print_color_message_t("----(" + to_string(i) + ")", 14);
			if (result) {
				passed++;
				Test_status_water_waves_sub.push_back({ test_description,"PASSED" });
				print_color_message_t("TEST PASSED\n", 10);
			}
			else {
				failed++;
				Test_status_water_waves_sub.push_back({ test_description,"FAILED" });
				print_color_message_t("TEST FAILED\n", 12);
			}
		}
		if (passed != 0) { print_color_message_t("\n- PASSED TESTS:     " + to_string(passed) + "\n", 10); }
		if (failed != 0) { print_color_message_t("\n- FAILED TESTS:     " + to_string(failed) + "\n", 12); }
		print_color_message_t("- PASSED TESTS PER: " + to_string((double)(100.0 * passed) / (double)total_tests) + " %\n\n", 14);
	};

	void execute_target_movement_test() {
		Target_Movement_T test;
		std::string Test_Category = ExePath_t() + "\\Tests\\Input_Data_Target_Movement.json";
		int total_tests = json_reader_get_total_num(Test_Category), i, passed = 0, failed = 0;
		bool result;

		print_color_message_t("\n-------- TARGET MOVEMENT TESTS TOTAL: " + to_string(total_tests) + " --------\n", 6);
		for (i = 1; i <= total_tests; i++) {
			result = test.target_movement_test("Test_" + to_string(i), this->Logs_Path, Test_Category, i, this->argv);
			std::string test_description = (json_reader_data_test_description(Test_Category,"Test_" + to_string(i)));
			print_color_message_t("----(" + to_string(i) + ")", 14);
			if (result) {
				passed++;
				Test_status_movement.push_back({ test_description,"PASSED" });
				print_color_message_t("TEST PASSED\n", 10);
			}
			else {
				failed++;
				Test_status_movement.push_back({ test_description,"FAILED" });
				print_color_message_t("TEST FAILED\n", 12);
			}
		}

		int counter = 1;
		print_color_message_t("\n---- Integration Tests\n", 10);
		if (passed != 0) { print_color_message_t("\n- PASSED TESTS:     " + to_string(passed) + "\n", 10); }
		if (failed != 0) { print_color_message_t("\n- FAILED TESTS:     " + to_string(failed) + "\n", 12); }
		print_color_message_t("- PASSED TESTS PER: " + to_string((double)(100.0 * passed) / (double)total_tests) + " %\n\n", 14);
	}

	void execute_unit_test(std::string timestmp) {
		set_up_unit_test();
		print_color_message_t("\n--------------------- RUN ALL UNIT TEST --------------------------------\n", 47);

		print_color_message_t("\n--------------- TEST COLLISION AVOIDANCE --------------------\n", 48);
		this->Logs_Path = create_Logs("Collision_avoidance", timestmp);
		execute_collision_avoidance_test();

		print_color_message_t("\n--------------- TEST WATER KINEMATIS ------------------------\n", 48);
		this->Logs_Path = create_Logs("Water_Wave_Kinematics", timestmp);
		this->Logs_Path_2 = create_Logs("Water_Wave_Kinematics_Subwater", timestmp);
		execute_water_kinematis_test();
		
		print_color_message_t("\n--------------- TEST POSSITION PREDICTION -------------------\n", 48);
		this->Logs_Path = create_Logs("Possition_Prediction", timestmp);
		execute_possition_prediction_test();
	}

	void execute_integration_test(std::string timestmp) {
		print_color_message_t("\n--------------------- RUN ALL INTEGRATION TEST --------------------------------\n", 47);
		print_color_message_t("\n--------------- TEST TARGET MOVEMENT --------------------\n", 48);
		this->Logs_Path = create_Logs("Target_Movement", timestmp);

		execute_target_movement_test();

	}

	void print_test_summary() {
		ofstream MyFile(this->logs_current_summary);
		print_color_message_t("\n--------------- TEST WATER KINEMATIS ------------------------\n", COLOR_TEXT::MAIN_TITLE_YELLOW);
		MyFile << "\n--------------- TEST WATER KINEMATIS ------------------------\n";
		int counter = 1;
		if (Test_status_water_waves.size() == 0) {
			cout << "-- No tests executed" << endl;
			MyFile << "--No tests executed\n";
		}
		else {
			for (vector<data >::const_iterator it = Test_status_water_waves.begin(); it != Test_status_water_waves.end(); ++it) {
				if (counter < 10) {
					print_color_message_t("-- test water waves " + to_string(counter) + "  :", 14);
					MyFile << "-- test water waves " + to_string(counter) + "  :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				else {
					print_color_message_t("-- test water waves " + to_string(counter) + " :", 14);
					MyFile << "-- test water waves " + to_string(counter) + " :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				MyFile << " " + it->status + ", " + it->description + "\n";
				counter++;
			}
		}

		print_color_message_t("\n--------------- TEST WATER KINEMATIS SUBWATER ---------------\n", COLOR_TEXT::MAIN_TITLE_YELLOW);
		MyFile << "\n--------------- TEST WATER KINEMATIS SUBWATER ---------------\n";
		counter = 1;
		if (Test_status_water_waves_sub.size() == 0) {
			cout << "-- No tests executed" << endl;
			MyFile << "-- No tests executed\n";
		}
		else {
			for (vector<data >::const_iterator it = Test_status_water_waves_sub.begin(); it != Test_status_water_waves_sub.end(); ++it) {
				if (counter < 10) {
					print_color_message_t("-- test water waves " + to_string(counter) + "  :", 14);
					MyFile << "-- test water waves " + to_string(counter) + "  :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				else {
					print_color_message_t("-- test water waves " + to_string(counter) + " :", 14);
					MyFile << "-- test water waves " + to_string(counter) + " :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				MyFile << " " + it->status + ", " + it->description + "\n";
				counter++;
			}
		}

		print_color_message_t("\n--------------- TEST COLLISION AVOIDANCE  ---------------\n", COLOR_TEXT::MAIN_TITLE_YELLOW);
		MyFile << "\n--------------- TEST COLLISION AVOIDANCE --------------------\n";
		counter = 1;
		if (Test_status_collision.size() == 0) {
			cout << "-- No tests executed" << endl;
			MyFile << "--No tests executed\n";
		}
		else {
			for (vector< data >::const_iterator it = Test_status_collision.begin(); it != Test_status_collision.end(); ++it) {
				if (counter < 10) {
					print_color_message_t("-- test collision avoidance " + to_string(counter) + "  :", 14);
					MyFile << "-- test collision avoidance " + to_string(counter) + "  :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				else {
					print_color_message_t("-- test collision avoidance " + to_string(counter) + " :", 14);
					MyFile << "-- test collision avoidance " + to_string(counter) + " :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				MyFile << " " + it->status + ", " + it->description + "\n";
				counter++;
			}
		}

		print_color_message_t("\n--------------- TEST POSSITION PREDICTION --------------\n", COLOR_TEXT::MAIN_TITLE_YELLOW);
		MyFile << "\n--------------- TEST POSSITION PREDICTION -------------------\n";
		counter = 1;
		if (Test_status_collision.size() == 0) {
			cout << "-- No tests executed" << endl;
			MyFile << "--No tests executed\n";
		}
		else {
			for (vector< data >::const_iterator it = Test_status_prediction.begin(); it != Test_status_prediction.end(); ++it) {
				if (counter < 10) {
					print_color_message_t("-- test possition prediction " + to_string(counter) + "  :", 14);
					MyFile << "-- test possition prediction " + to_string(counter) + "  :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				else {
					print_color_message_t("-- test possition prediction " + to_string(counter) + " :", 14);
					MyFile << "-- test possition prediction " + to_string(counter) + " :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				MyFile << " " + it->status + ", " + it->description + "\n";
				counter++;
			}
		}

		print_color_message_t("\n--------------- TEST TARGET MOVEMENT --------------------\n", COLOR_TEXT::MAIN_TITLE_YELLOW);
		MyFile << "\n--------------- TEST TARGET MOVEMENT ------------------------\n";
		counter = 1;
		if (Test_status_movement.size() == 0) {
			cout << "-- No tests executed" << endl;
			MyFile << "--No tests executed\n";
		}
		else{
			for (vector< data >::const_iterator it = Test_status_movement.begin(); it != Test_status_movement.end(); ++it) {
				if (counter < 10) {
					print_color_message_t("-- test target movement " + to_string(counter) + "  :", 14);
					MyFile << "-- test target movement " + to_string(counter) + "  :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				else {
					print_color_message_t("-- test target movement " + to_string(counter) + " :", 14);
					MyFile << "-- test target movement " + to_string(counter) + " :";
					if (it->status == "PASSED") {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::GREEN_COLOR);
					}
					else {
						print_color_message_t(" " + it->status + " ,", COLOR_TEXT::RED_COLOR);
					}
					print_color_message_t(it->description + "\n", 14);
				}
				MyFile << " " + it->status + ", " + it->description + "\n";
			}
			counter++;
		}
		MyFile.close();
		cout << "\n\n-- Note: check test summary in :" << this->logs_current_summary <<endl<<endl;
	}


public:

	Run_tests(int argc, char* argv[]) {
		this->argc = argc;
		this->argv = argv;
	}
	~Run_tests() {
		delete this->detector_c;
		delete this->detector_p;
		delete this->detector_w;
		delete this->event;
	};
	
	void execute_all_tests() {
		std::string timestmp = getTimestamp_t();
	    this->logs_current_summary = "Test_Logs\\Test_Logs_" + timestmp + "\\Test_Summary.txt";

		execute_unit_test(timestmp);
		execute_integration_test(timestmp);
		print_test_summary();

		ofstream MyFile("Test_Logs\\Test_Logs_" + timestmp + "\\Read_Me.txt");
		MyFile << "----------------- TEST COMMAND EXECUTION TUTORIAL ----------------- \n\n\n";
		MyFile << "WATER WAVES SURFACE    : In folder -> Water_Wave_Kinematics          Execute 'python3 Water_Wave_Kinematics.py 2d_surface_waves_1.txt'\n";
		MyFile << "WATER WAVES SUBWATER   : In folder -> Water_Wave_Kinematics_Subwater Execute 'python3 Water_Wave_Kinematics_Subwater.py 3d_current_waves_1.txt'\n";
		MyFile << "COLLISION AVOIDANCE    : In folder -> Collision_avoidance            Execute 'python3 Collision_avoidance.py Logs1.txt'\n";
		MyFile << "POSSITION PREDICTION   : In folder -> Possition_Prediction           Execute 'python3 Possition_Prediction.py '\n";
		MyFile << "TARGET MOVEMENT Target : In folder -> Target_Movement/*/Movements    Execute 'python3 movement'\n";
		MyFile << "TARGET MOVEMENT Fields : In folder -> Target_Movement/*/Fields/*/    Execute 'python3 {relevant field script 2d or 3d if exists}'\n";
		MyFile.close();
	}

};
#endif