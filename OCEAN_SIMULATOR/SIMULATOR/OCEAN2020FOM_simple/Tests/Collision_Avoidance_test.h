#pragma once
#ifndef COLLISION_AVOIDANCE_T_H
#define COLLISION_AVOIDANCE_T_H

#include "Helper_Header.h"

using namespace std;

class Collision_Avoidance_T {
public:
	bool collision_avoidance_test(std::map<std::string, double> data, std::string Logs_Collision,int stamp, Collision_Avoidance *detector) {
		bool result = false;
		if (data["description"] == 0.0) {
			result = collision_avoidance_test_1(data, Logs_Collision, stamp, detector);
		}
		else {
			result = collision_avoidance_test_2(data, Logs_Collision, stamp, detector);
		}
		return result;
	}

	bool collision_avoidance_test_1(std::map<std::string, double> data, std::string Logs_Collision, 	int stamp, Collision_Avoidance *detector) {

		std::string fieldpath = Logs_Collision + "\\" + "Logs" + to_string(stamp) + ".txt";
		ofstream logs(fieldpath);
		double diss = 0, xe = 0, ye = 0, re = 0;
		double obstacle_x = data["obstacle_x"];
		double obstacle_y = data["obstacle_y"];
		double obstacle_angle = data["obstacle_angle"];
		double obstacle_velocity = data["obstacle_velocity"];

		double vessel_x = data["vessel_x"];
		double vessel_y = data["vessel_y"];
		double vessel_angle = data["vessel_angle"];
		double vessel_velocity = data["vessel_velocity"];
		double vessel_angle_velocity = data["vessel_angle_velocity"];

		double target_x = data["target_x"];
		double target_y = data["target_y"];
		double vessel_radius = data["vessel_radius"];
		double obstacle_radius = data["obstacle_radius"];

		double safe_distance = data["safe_distance"];
		double avoid_distance = data["avoid_distance"];
		double axis_x = data["axis_x"];
		double axis_y = data["axis_y"];
		double max_speed = 30;
		bool emegercy_on = false;

		bool test1 = false;
		bool test2 = false;
		int counter = 0;
		while (counter <= 1000) {

			test1 = detector->collision_avoidance_start(vessel_velocity, vessel_angle,	obstacle_velocity, obstacle_angle,	vessel_x, vessel_y, 0,obstacle_x, obstacle_y, 0, safe_distance, avoid_distance,1, vessel_angle_velocity, emegercy_on, max_speed);
			if (test2) {
				break;
			}

			move_to_direction(vessel_x, vessel_y, vessel_velocity, vessel_angle);
			move_to_direction(obstacle_x, obstacle_y, obstacle_velocity, obstacle_angle);

			if (circles_intersection(vessel_x, vessel_y, target_x, target_y, vessel_radius, 10)) { break; }

			if (!test1) {
				vessel_angle = angle_balancing_equalizer(vessel_x, vessel_y, target_x, target_y, vessel_angle,	vessel_angle_velocity, vessel_velocity);
			}
			detector->check_eccentric_expansion(xe, ye, re);
			logs << (vessel_x) << " " << (vessel_y) << " "<< (obstacle_x) << " " << (obstacle_y) << " "	<< xe << " " << ye << " " << re << "\n";
			counter++;
		}
		logs << vessel_radius << " " << obstacle_radius << " " << safe_distance << " " << avoid_distance << endl;
		logs << axis_x << " " << axis_y << endl;
		logs.close();
		if (test2 || counter > 1000) { return false; }
		else { return true; }
	}

	bool collision_avoidance_test_2(std::map<std::string, double> data, std::string Logs_Collision, 
										int stamp, Collision_Avoidance *detector) {
		class Obstacle {
		public:
			double obstacle_x;
			double obstacle_y;
			double obstacle_angle;
			double obstacle_velocity;
		};
		std::string fieldpath = Logs_Collision + "\\" + "Logs" + to_string(stamp) + ".txt";
		ofstream logs(fieldpath);
		int obstacles = int(data["description"]);
		Obstacle *obs = new Obstacle[obstacles];
		double xe = 0, ye = 0, re = 0;
		for (int i = 0; i < obstacles; i++) {
			obs[i].obstacle_x = data["obstacle_x_" + to_string(i+1)];
			obs[i].obstacle_y = data["obstacle_y_" + to_string(i + 1)];
			obs[i].obstacle_angle = data["obstacle_angle_" + to_string(i + 1)];
			obs[i].obstacle_velocity = data["obstacle_velocity_" + to_string(i + 1)];

		}

		double vessel_x = data["vessel_x"];
		double vessel_y = data["vessel_y"];
		double vessel_angle = data["vessel_angle"];
		double vessel_velocity = data["vessel_velocity"];
		double vessel_angle_velocity = data["vessel_angle_velocity"];

		double target_x = data["target_x"];
		double target_y = data["target_y"];
		double vessel_radius = data["vessel_radius"];
		double obstacle_radius = data["obstacle_radius"];

		double safe_distance = data["safe_distance"];
		double avoid_distance = data["avoid_distance"];
		double axis_x = data["axis_x"];
		double axis_y = data["axis_y"];

		bool test1 = false;
		bool test2 = false;
		int counter = 0;
		while (counter <= 1000) {
			for (int i = 0; i < obstacles; i++) {

				/*test1 = detector.collision_avoidance_start(
					vessel_velocity, vessel_angle,
					obstacle_velocity, obstacle_angle,
					vessel_x, vessel_y, 0,
					obstacle_x, obstacle_y, 0,
					vessel_radius, obstacle_radius, safe_distance, avoid_distance,
					vessel_radius, obstacle_radius,
					1, vessel_angle_velocity);

				test2 = detector.check_collision_destuction();
				if (test2) {
					break;
				}

				move_to_direction(vessel_x, vessel_y, vessel_velocity, vessel_angle);
				move_to_direction(obstacle_x, obstacle_y, obstacle_velocity, obstacle_angle);

				if (circles_intersection(vessel_x, vessel_y, target_x, target_y, vessel_radius, 10)) { break; }

				if (!test1) {
					vessel_angle = angle_balancing_equalizer(vessel_x, vessel_y, target_x, target_y, vessel_angle,
						vessel_angle_velocity, vessel_velocity);
				}
				detector.check_eccentric_expansion(xe, ye, re);
				logs << (vessel_x) << " " << (vessel_y) << " "
					<< (obstacle_x) << " " << (obstacle_y) << " "
					<< xe << " " << ye << " " << re << "\n";*/
				counter++;
			}
		}
		logs << vessel_radius << " " << obstacle_radius << " " << safe_distance << " " << avoid_distance << endl;
		logs << axis_x << " " << axis_y << endl;
		logs.close();
		delete obs;
		if (test2 || counter > 1000) { return false; }
		else { return true; }
	}

};
#endif