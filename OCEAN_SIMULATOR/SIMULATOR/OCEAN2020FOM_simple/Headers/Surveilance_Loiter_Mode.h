#pragma once
#ifndef SURVEILANCE_LOITER_MODE_H
#define SURVEILANCE_LOITER_MODE_H

#include "Data_Stuctures.h"
namespace Surveilance_Loiter {

	/******************* PATROLING ******************/
	void patroling(VESSEL_KINEMATICS *vessel_kinematics, VESSEL_CHARACTERISTICS* vessel_char,
		list<Point*>::iterator current_patroling_point, std::list<Point*> patroling_points) {
		double curr_x = vessel_kinematics->get_current_x();
		double curr_y = vessel_kinematics->get_current_y();

		double patroling_target_x = (*current_patroling_point)->x();
		double patroling_target_y = (*current_patroling_point)->y();

		double theta_dest_horiz;

		if (vessel_char->get_type() == "SURFACE") {
			double dist_curr_to_patroling_target = point_distance(curr_x, curr_y, patroling_target_x, patroling_target_y);
			if (dist_curr_to_patroling_target < vessel_char->get_area() / 2) {
				if ((current_patroling_point != patroling_points.end()) && (next_iteration(current_patroling_point) == patroling_points.end()))
				{
					current_patroling_point = patroling_points.begin();
				}
				current_patroling_point = (++current_patroling_point);
			}
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, (*current_patroling_point)->x(), (*current_patroling_point)->y());
			vessel_kinematics->set_destination_xyz((*current_patroling_point)->x(), (*current_patroling_point)->y(), 0);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
		}
		else {
			double curr_z = vessel_kinematics->get_current_z();
			double patroling_target_z = (*current_patroling_point)->z();
			double theta_dest_vertical;

			double dist_curr_to_patroling_target = point_distance_3d(curr_x, curr_y, curr_z, patroling_target_x, patroling_target_y, patroling_target_z);

			if ((dist_curr_to_patroling_target < vessel_char->get_area() / 2) && (patroling_target_z < (vessel_kinematics->get_current_z() + vessel_char->get_height()))) {
				if ((current_patroling_point != patroling_points.end()) && (next_iteration(current_patroling_point) == patroling_points.end()))
				{
					current_patroling_point = patroling_points.begin();
				}
				current_patroling_point = (++current_patroling_point);
			}
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, (*current_patroling_point)->x(), (*current_patroling_point)->y());
			theta_dest_vertical = angle_between_3d_points(curr_x, curr_y, curr_z,
				(*current_patroling_point)->x(),
				(*current_patroling_point)->y(),
				(*current_patroling_point)->z());
			vessel_kinematics->set_destination_xyz((*current_patroling_point)->x(), (*current_patroling_point)->y(), (*current_patroling_point)->z());
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
			vessel_kinematics->set_destination_theta_vertical(theta_dest_vertical);
		}
	}

	/******************* RESET **********************/
	void reset(VESSEL_KINEMATICS *vessel_kinematics, VESSEL_CHARACTERISTICS* vessel_char,
		list<Point*>::iterator current_patroling_point, std::list<Point*> patroling_points,
		bool *reset_mode_on, char* job) {

		double curr_x = vessel_kinematics->get_current_x();
		double curr_y = vessel_kinematics->get_current_y();

		double reset_target_x = vessel_kinematics->get_deploy_x();
		double reset_target_y = vessel_kinematics->get_deploy_y();

		double theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, (*current_patroling_point)->x(), (*current_patroling_point)->y());

		if (vessel_char->get_type() == "SURFACE") {
			double dist_curr_to_reset_target = point_distance(curr_x, curr_y, reset_target_x, reset_target_y);
			if (dist_curr_to_reset_target < vessel_char->get_area() / 2) {
				current_patroling_point = patroling_points.begin();
				vessel_kinematics->set_destination_xyz((*current_patroling_point)->x(), (*current_patroling_point)->y(), 0);
				vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
				*reset_mode_on = false;
				*job = 'P';
			}
			else {
				theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, reset_target_x, reset_target_y);
				vessel_kinematics->set_destination_xyz(reset_target_x, reset_target_y, 0);
				vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
				*job = 'R';
			}
		}
		else {
			double curr_z = vessel_kinematics->get_current_z();
			double reset_target_z = vessel_kinematics->get_deploy_z();
			double dist_curr_to_reset_target = point_distance_3d(curr_x, curr_y, curr_z, reset_target_x, reset_target_y, reset_target_z);

			if (dist_curr_to_reset_target < vessel_char->get_area() / 2) {
				current_patroling_point = patroling_points.begin();
				double theta_dest_vetical = angle_between_3d_points(curr_x, curr_y, curr_z,
					(*current_patroling_point)->x(), (*current_patroling_point)->y(), (*current_patroling_point)->z());
				vessel_kinematics->set_destination_xyz((*current_patroling_point)->x(), (*current_patroling_point)->y(), (*current_patroling_point)->z());
				vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
				vessel_kinematics->set_destination_theta_vertical(theta_dest_vetical);
				*reset_mode_on = false;
				*job = 'P';
			}
			else {
				theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, reset_target_x, reset_target_y);
				double theta_dest_vetical = angle_between_3d_points(curr_x, curr_y, curr_z, reset_target_x, reset_target_y, reset_target_z);
				vessel_kinematics->set_destination_xyz(reset_target_x, reset_target_y, reset_target_z);
				vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
				vessel_kinematics->set_destination_theta_vertical(theta_dest_vetical);
				*job = 'R';
			}
		}
	}
}
#endif