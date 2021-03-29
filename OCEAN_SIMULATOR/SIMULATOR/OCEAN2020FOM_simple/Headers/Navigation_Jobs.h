#pragma once
#include "Data_Stuctures.h"

/******************************************************************************/
/*************************** NAVIGATION JOBS **********************************/
/******************************************************************************/


namespace Navigation {
	
	/******************* move linear ****************/
	void move(VESSEL_KINEMATICS *kinematics_status, VESSEL_MOTION_VALUES *vessel_motion, VESSEL_CHARACTERISTICS* vessel_char, DtTime dt) {
		double x0, y0;
		double z0;
		x0 = kinematics_status->get_current_x();
		y0 = kinematics_status->get_current_y();
		if (vessel_char->get_type() == "SUB_ROV") {
			double temp_z_dir;
			temp_z_dir = vessel_motion->get_acceleration_decent();
			z0 = kinematics_status->get_current_z();
			move_to_direction(x0, y0, vessel_motion->get_speed(), kinematics_status->get_current_theta_horizontal());
			if (abs(abs(kinematics_status->get_destination_z()) - abs(z0)) < 0.5) {
				z0 = kinematics_status->get_destination_z();
			}
			else {
				if (kinematics_status->get_destination_z() < z0) {
					z0 = z0 - temp_z_dir;
					if (kinematics_status->get_destination_z() >= z0) {
						z0 = kinematics_status->get_destination_z();
					}
				}
				else {
					z0 = z0 + temp_z_dir;
					if (kinematics_status->get_destination_z() <= z0) {
						z0 = kinematics_status->get_destination_z();
					}
				}
				if (z0 > -(vessel_char->get_height())) {
					z0 = -(vessel_char->get_height());
				}
			}
		}
		else {
			z0 = 0.0;
		}
		double psi = DtDeg2Rad(kinematics_status->get_current_theta_horizontal());

		double vx = kinematics_status->get_current_x();
		double vy = kinematics_status->get_current_y();

		x0 = kinematics_status->get_current_x() + (vessel_motion->get_speed_x() + 0.5 * vessel_motion->get_acceleration_x() * dt) *dt;
		y0 = kinematics_status->get_current_y() + (vessel_motion->get_speed_y() + 0.5 * vessel_motion->get_acceleration_y() * dt) *dt;

		vessel_motion->set_speed_comp_x(vessel_motion->get_speed_x() + vessel_motion->get_acceleration_x() * dt);
		vessel_motion->set_speed_comp_y(vessel_motion->get_speed_y() + vessel_motion->get_acceleration_y() * dt);
		vessel_motion->set_speed_comp_z(vessel_motion->get_speed_z() + vessel_motion->get_acceleration_z() * dt);

		double vel = sqrt(pow(vessel_motion->get_speed_x(), 2) + pow(vessel_motion->get_speed_y(), 2));
		vessel_motion->set_speed(vel);

		vessel_motion->set_acceleration_comp_x(vessel_motion->get_acceleration() * cos(psi));
		vessel_motion->set_acceleration_comp_y(vessel_motion->get_acceleration() * sin(psi));
		vessel_motion->set_acceleration_comp_z(0.0);

		kinematics_status->set_current_xyz(x0, y0, z0);

	}

	/************* speed_balancing_equalizer ********/
	void speed_balancing_equalizer(VESSEL_KINEMATICS *kinematics_status, VESSEL_MOTION_VALUES *vessel_motion, VESSEL_CHARACTERISTICS* vessel_char, DtTime dt) {
		double acceleration = vessel_motion->get_acceleration() ;
		double max_acceleration = vessel_motion->get_Max_acceleration() ;
		double dist_curr_to_target =  point_distance_3d(kinematics_status->get_current_x(), kinematics_status->get_current_y(), kinematics_status->get_current_z(),kinematics_status->get_destination_x(), kinematics_status->get_destination_y(), kinematics_status->get_destination_z());
		double psi = DtDeg2Rad(kinematics_status->get_current_theta_horizontal());

		double angle_deviation_hor = (kinematics_status->get_current_theta_horizontal() - kinematics_status->get_destination_theta_horizontal());
		angle_deviation_hor = std::fmod((angle_deviation_hor + 180), 360) - 180;
		angle_deviation_hor = std::fabs(angle_deviation_hor);
		
		double vel = vessel_motion->get_speed();
		vessel_motion->set_velocity_status(check_acceleration_deceleration(acceleration,max_acceleration,dist_curr_to_target, vel, angle_deviation_hor, dt));

		vessel_motion->set_acceleration(acceleration );
		vessel_motion->set_acceleration_comp_x(vessel_motion->get_acceleration() * cos(psi));
		vessel_motion->set_acceleration_comp_y(vessel_motion->get_acceleration() * sin(psi));
		vessel_motion->set_acceleration_comp_z(0.0);
		if (vessel_motion->get_speed() +acceleration >= vessel_motion->get_Max_speed()) {
			vessel_motion->set_speed(vessel_motion->get_Max_speed());
			vessel_motion->set_speed_comp_x(vessel_motion->get_Max_speed()*cos(DtDeg2Rad(kinematics_status->get_current_theta_horizontal())));
			vessel_motion->set_speed_comp_y(vessel_motion->get_Max_speed()*sin(DtDeg2Rad(kinematics_status->get_current_theta_horizontal())));
			vessel_motion->set_speed_comp_z(0.0);

			vessel_motion->set_acceleration(0.0);
			vessel_motion->set_acceleration_comp_x(0.0);
			vessel_motion->set_acceleration_comp_y(0.0);
			vessel_motion->set_acceleration_comp_z(0.0);
		}
		if (vel <= 0) {
			vessel_motion->set_speed_comp_x(0.0);
			vessel_motion->set_speed_comp_y(0.0);
			vessel_motion->set_speed_comp_z(0.0);
			vessel_motion->set_speed(0.0);
		}
		
		/*if (dist_curr_to_target <= 10) {
			vessel_motion->set_speed_comp_x(0.0);
			vessel_motion->set_speed_comp_y(0.0);
			vessel_motion->set_speed_comp_z(0.0);
			vessel_motion->set_speed(0.0);

			vessel_motion->set_acceleration(0.0);
			vessel_motion->set_acceleration_comp_x(0.0);
			vessel_motion->set_acceleration_comp_y(0.0);
			vessel_motion->set_acceleration_comp_z(0.0);
		}*/

		if (dist_curr_to_target > 1000) {
			vessel_motion->set_speed_comp_x(0.0);
			vessel_motion->set_speed_comp_y(0.0);
			vessel_motion->set_speed_comp_z(0.0);
			vessel_motion->set_speed(0.0);
		}
	}

	/************* angle_balancing_equalizer ********/
	void angle_balancing_equalizer(VESSEL_KINEMATICS *kinematics_status, VESSEL_MOTION_VALUES *vessel_motion, VESSEL_CHARACTERISTICS* vessel_char, DtTime dt, bool waves) {
		double theta_left;
		double theta_right;
		double x_left, y_left;
		double x_right, y_right;
		double angular_velocity = vessel_motion->get_Max_angle_speed();
		double linear_velocity = vessel_motion->get_speed();

		double destination_angle = kinematics_status->get_destination_theta_horizontal();
		double current_angle = kinematics_status->get_current_theta_horizontal();

		x_left = kinematics_status->get_current_x();
		y_left = kinematics_status->get_current_y();

		x_right = kinematics_status->get_current_x();
		y_right = kinematics_status->get_current_y();

		theta_left = kinematics_status->get_current_theta_horizontal();
		theta_right = kinematics_status->get_current_theta_horizontal();
	
		double psi_l=0.0,psi_r=0.0;
		double angle_diff = (kinematics_status->get_destination_theta_horizontal() - kinematics_status->get_current_theta_horizontal()); 
		angle_diff = std::fmod((angle_diff + 180), 360) - 180;
		angle_diff = std::fabs(angle_diff);
		if ( angle_diff >= (angular_velocity + 5 )) {
			double theta_turned = theta_left - angular_velocity;
			psi_l = DtModPerZero((DtDeg2Rad(theta_left) - (DtDeg2Rad(angular_velocity) * dt)), M_2PI);
			psi_l = DtRad2Deg( psi_l);
			double theta_turned_norm_left = angle_degree_normalization(theta_turned);
			move_to_direction(x_left, y_left, linear_velocity, theta_turned_norm_left);
			
			theta_turned = theta_right + angular_velocity;
			psi_r = DtModPerZero((DtDeg2Rad(theta_right) + (DtDeg2Rad(angular_velocity) * dt)), M_2PI);
			psi_r = DtRad2Deg(psi_r);		
			double theta_turned_norm_rigth = angle_degree_normalization(theta_turned);
			move_to_direction(x_right, y_right, linear_velocity, theta_turned_norm_rigth);

			double distance_from_left = point_distance(x_left, y_left, kinematics_status->get_destination_x(), kinematics_status->get_destination_y());
			double distance_from_right = point_distance(x_right, y_right, kinematics_status->get_destination_x(), kinematics_status->get_destination_y());
			
			if (distance_from_left < distance_from_right) {
				kinematics_status->set_current_theta_horizontal(psi_l);
			}
			else {
				kinematics_status->set_current_theta_horizontal(psi_r);
			}
		}
		else {
			double tmp = kinematics_status->get_destination_theta_horizontal();
			kinematics_status->set_current_theta_horizontal(tmp);
		}
	}

	/******************* radar_detection ************/
	bool radar_detection(double x0, double y0, double x1, double y1, double radius) {
		return point_is_in_range(x0, y0, x1, y1, radius);
	}

	/******************* depth_detection ************/
	bool depth_detection(double x0, double y0, double x1, double y1, double radius) {

		return true;
	}

	/******************* compass direction **********/
	char *display_compass_direction(double x0, double y0, double x1, double y1) {
		return compass_direction_in_string(x0, y0, x1, y1);
	}

}