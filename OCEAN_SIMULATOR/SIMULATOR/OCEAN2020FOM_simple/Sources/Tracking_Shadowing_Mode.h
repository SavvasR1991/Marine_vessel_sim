#pragma once
#ifndef TRACKING_SHADOWING_MODE_H
#define TRACKING_SHADOWING_MODE_H

#include "Data_Stuctures.h"
#include "General_functions.h"

namespace Tracking_Shadowing {

	/******************* VANGUARED ******************/
	void vanguared(VESSEL_KINEMATICS *vessel_kinematics, VESSEL_CHARACTERISTICS* vessel_char, double x_target, double y_target, double z_target, std::vector<SHADOWING_TEAM_DATA*>  *shadow_team, char *job, double vanguard_distance, double vanguard_distance_depth) {
		double x_target_tmp = x_target;
		double y_target_tmp = y_target;
		double z_target_tmp = z_target;
		double curr_x = vessel_kinematics->get_current_x();
		double curr_y = vessel_kinematics->get_current_y();
		double theta_dest_horiz, xBeforeRotation = 0, yBeforeRotation = 0, direction = -1;
		double lock_distance = 100;
		bool reverse = false;

		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin((*shadow_team)); it != std::end((*shadow_team)); ++it) {
			if ((*it)->get_name() == vessel_char->get_name()) {
				xBeforeRotation = (*it)->get_coord_X_BeforeRotation();
				yBeforeRotation = (*it)->get_coord_Y_BeforeRotation();
				direction = (*it)->get_direction();
				break;
			}
		}

		if (y_target >= vessel_kinematics->get_reference_y()) { // Top
			double amgle_new = angle_between_2d_points(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), x_target, y_target);
			double dist_new = point_distance(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), x_target, y_target);
			double vertical = dist_new * sin(degrees_to_radians(amgle_new));
			double theta_rad = degrees_to_radians(270);
			y_target = vessel_kinematics->get_reference_y() + vertical * sin(theta_rad);
			reverse = true;
		}

		if (vessel_char->get_type() == "SURFACE") {
			z_target_tmp = 0;
		}
		else {
			z_target_tmp = z_target_tmp + vanguard_distance_depth;// vanguard_distance* NORMALIZER_GEODIC_MINUTES_TO_METERS;
		}

		if (direction >= 0) {
			double angleOfRotation = findAngleOfRotation(x_target, y_target, vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y());
			double new_point_x = 0, new_point_y = 0;
			calculatePositionOfNodeAfterRotation(x_target, y_target, xBeforeRotation, yBeforeRotation, angleOfRotation, direction, new_point_x, new_point_y);
			if (reverse == true) {
				double amgle_new = angle_between_2d_points(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), new_point_x, new_point_y);
				double dist_new = point_distance(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), new_point_x, new_point_y);
				double vertical = dist_new * sin(degrees_to_radians(amgle_new));
				double theta_rad = degrees_to_radians(90);
				new_point_y = vessel_kinematics->get_reference_y() + abs(vertical);
			}
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, new_point_x, new_point_y);
			vessel_kinematics->set_destination_xyz(new_point_x, new_point_y, z_target_tmp);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
			if (point_distance(curr_x, curr_y, new_point_x, new_point_y) < lock_distance) {
				*job = JOB::LOCK;
			}
		}
		else {
			cout << curr_x << " " << curr_y << " " << x_target_tmp << " " << y_target_tmp << endl;
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, x_target_tmp, y_target_tmp);
			vessel_kinematics->set_destination_xyz(x_target_tmp, y_target_tmp, z_target_tmp);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);

			if (point_distance(curr_x, curr_y, x_target_tmp, y_target_tmp) < lock_distance) {
				*job = JOB::LOCK;
			}
		}
	}

	/******************* LOCK ***********************/
	void lock(VESSEL_KINEMATICS *vessel_kinematics, VESSEL_CHARACTERISTICS* vessel_char, double x_target, double y_target, double z_target, std::vector<SHADOWING_TEAM_DATA*>  *shadow_team, char *job, bool *team_lock, double vanguard_distance, double vanguard_distance_depth) {
		double curr_x = vessel_kinematics->get_current_x();
		double curr_y = vessel_kinematics->get_current_y();
		double x_target_tmp = x_target;
		double y_target_tmp = y_target;
		double z_target_tmp = z_target;
		double theta_dest_horiz, xBeforeRotation = 0, yBeforeRotation = 0, direction = 0;
		bool check_team_is_lock = true;
		bool reverse = false;

		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin((*shadow_team)); it != std::end((*shadow_team)); ++it) {
			if ((*it)->get_name() == vessel_char->get_name()) {
				xBeforeRotation = (*it)->get_coord_X_BeforeRotation();
				yBeforeRotation = (*it)->get_coord_Y_BeforeRotation();
				direction = (*it)->get_direction();
				(*it)->set_job(JOB::LOCK);
			}
			if ((*it)->get_job() != JOB::LOCK) {
				check_team_is_lock = false;
			}
		}

		if (y_target >= vessel_kinematics->get_reference_y()) { // Top
			double amgle_new = angle_between_2d_points(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), x_target, y_target);
			double dist_new = point_distance(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), x_target, y_target);
			double vertical = dist_new * sin(degrees_to_radians(amgle_new));
			double theta_rad = degrees_to_radians(270);
			y_target = vessel_kinematics->get_reference_y() + vertical * sin(theta_rad);
			reverse = true;
		}
		if (vessel_char->get_type() == "SURFACE") {
			z_target_tmp = 0;
		}
		else {
			z_target_tmp = z_target_tmp + vanguard_distance_depth;// vanguard_distance * NORMALIZER_GEODIC_MINUTES_TO_METERS;
		}
		if (direction >= 0) {
			*team_lock = check_team_is_lock;
			double angleOfRotation = findAngleOfRotation(x_target, y_target, vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y());
			double new_point_x = 0, new_point_y = 0;
			calculatePositionOfNodeAfterRotation(x_target, y_target, xBeforeRotation, yBeforeRotation, angleOfRotation, direction, new_point_x, new_point_y);
			if (reverse == true) {
				double amgle_new = angle_between_2d_points(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), new_point_x, new_point_y);
				double dist_new = point_distance(vessel_kinematics->get_reference_x(), vessel_kinematics->get_reference_y(), new_point_x, new_point_y);
				double vertical = dist_new * sin(degrees_to_radians(amgle_new));
				double theta_rad = degrees_to_radians(90);
				new_point_y = vessel_kinematics->get_reference_y() + abs(vertical);
			}
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, new_point_x, new_point_y);
			vessel_kinematics->set_destination_xyz(new_point_x, new_point_y, z_target_tmp);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
		}
		else {
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, x_target_tmp, y_target_tmp);
			vessel_kinematics->set_destination_xyz(x_target_tmp, y_target_tmp, z_target_tmp);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
		}
	}

	/******************* OVERSIGHT ******************/
	void oversight(VESSEL_KINEMATICS *vessel_kinematics, VESSEL_CHARACTERISTICS* vessel_char, list<Point*>::iterator &current_oversigh_point, std::list<Point*> &oversigh_points, std::string leader, double x, double y, double z) {
		double curr_x = vessel_kinematics->get_current_x();
		double curr_y = vessel_kinematics->get_current_y();
		double theta_dest_horiz;

		if (vessel_char->get_name() != leader) {
			double oversight_target_x = (*current_oversigh_point)->x();
			double oversight_target_y = (*current_oversigh_point)->y();

			double dist_curr_to_patroling_target = point_distance(curr_x, curr_y, oversight_target_x, oversight_target_y);
			if (dist_curr_to_patroling_target < vessel_char->get_area_radius() / 2) {
				if ((current_oversigh_point != oversigh_points.end()) && (next_iteration(current_oversigh_point) == oversigh_points.end()))
				{
					current_oversigh_point = oversigh_points.begin();
				}
				current_oversigh_point = (++current_oversigh_point);
			}
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, (*current_oversigh_point)->x(), (*current_oversigh_point)->y());
			vessel_kinematics->set_destination_xyz((*current_oversigh_point)->x(), (*current_oversigh_point)->y(), z);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
		}
		else {
			theta_dest_horiz = angle_between_2d_points(curr_x, curr_y, x,y);
			vessel_kinematics->set_destination_xyz(x, y, z);
			vessel_kinematics->set_destination_theta_horizontal(theta_dest_horiz);
		}
	}

}

#endif