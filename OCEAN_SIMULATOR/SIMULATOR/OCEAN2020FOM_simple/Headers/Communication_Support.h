#pragma once
#ifndef COMMINICATION_SUPPORT_H
#define COMMINICATION_SUPPORT_H

#include "Utils_Functions.h"


class Communication_Supporter {

private:

	double x_safe_point;
	double y_safe_point;
	double z_safe_point;

public:
	Communication_Supporter() {
		std::cout << "---- Communication supporter created" << std::endl;
	}

	~Communication_Supporter() {
		std::cout << "---- Communication supporter deleted" << std::endl;
	}

	void check_communication_status(VESSEL_KINEMATICS *kinematics, VESSEL_MOTION_VALUES* speed_vessel, bool &recovery_activation, Radio_Receiver* radio_receiver, char job) {
		double safe_x = kinematics->get_safe_point_x();
		double safe_y = kinematics->get_safe_point_y();
		double safe_z = kinematics->get_safe_point_z();
		double vel = speed_vessel->get_speed();
		if (vel > 0) {
			vel = vel - speed_vessel->get_deceleration();
			if (vel < 0) {
				vel = 0.0;
			}
			speed_vessel->set_speed(vel);
		}
		recovery_activation = true;
	}

	void set_safe_point(double x, double y, double z) {
		this->x_safe_point = x;
		this->y_safe_point = y;
		this->z_safe_point = z;
	}

	double get_safe_x() {
		return this->x_safe_point;
	}

	double get_safe_y() {
		return this->y_safe_point;
	}

	double get_safe_z() {
		return this->z_safe_point;
	}


};

#endif
