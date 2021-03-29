#pragma once
#ifndef POSSITION_PREDICTION_T_H
#define POSSITION_PREDICTION_T_H

#include "Helper_Header.h"


class Predictor_Position_T {

public:

	bool possition_avoidance_test(std::map<std::string, double> data, std::string Logs_Path, int stamp, Predictor_Position* detector) {
		
		std::string fieldpath = Logs_Path + "\\" + "Logs" + to_string(stamp) + ".txt";
		ofstream logs(fieldpath);
		double vessel_x = data["vessel_x"];
		double vessel_y = data["vessel_y"];
		double vessel_z = data["vessel_z"];
		double vessel_angle = data["vessel_angle"];
		double vessel_velocity = data["vessel_velocity"];
		double random_factor = data["random_factor"];
		double acceleration = data["vessel_velocity"];
		double vessel_angle_velocity = 2* data["vessel_angle_velocity"];
		double R_ = 0.01*0.01;
		double vessel_velocity_x = vessel_velocity;
		double vessel_velocity_y = vessel_velocity;
		double x_pred = vessel_x;
		double y_pred = vessel_y;
		int counter = 0;
		int iSecret = 0;
		double turn = -1;
		srand(time(NULL));

		while (counter <= 50) {
			iSecret = rand() % 10 + 1;
			detector->set_start_kalman_filter(&x_pred, &y_pred, vessel_x, vessel_y, R_);
			vessel_velocity_x = vessel_velocity_x + 2;
			if (10 - random_factor < iSecret) {
				turn = rand() % (2*(int)vessel_angle_velocity) + (-vessel_angle_velocity);
				vessel_angle = vessel_angle + turn ;
				angle_degree_normalization(vessel_angle);
			}
			move_to_direction(vessel_x, vessel_y, vessel_velocity_x, vessel_angle);
			logs << vessel_x << " " << vessel_y<< " "<< x_pred << " "<< y_pred <<"\n";
			counter++;
		}
		logs.close();
		return true;
	}

};
#endif