#pragma once
#ifndef HELPER_HEADER_H
#define HELPER_HEADER_H

#include <Windows.h>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Water_Waves_Kinematics.h"
#include "Collision_avoidance.h"

using namespace std;

namespace {

	void print_color_message_t(std::string message, int color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		std::cout << message << flush;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	std::string getTimestamp_t() {
		time_t now = time(0);
		char* dt = ctime(&now);
		std::string time_stamp(dt);
		for (int i = 0; i < time_stamp.length(); i++) {
			if (time_stamp[i] == ' ' || time_stamp[i] == ':') {
				time_stamp[i] = '_';
			}
		}
		return time_stamp.substr(0, time_stamp.size() - 1);
	}

	std::string ExePath_t() {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string myString = std::string(buffer).substr(0, pos);
		std::string st = myString.substr(0, myString.size() - 1);
		return st;
	}

	std::string create_Logs(std::string Scrpits, std::string timestmp) {
		print_color_message_t("\n----------- Set Up Log enviroment ----------------\n", 10);
		std::string simulator_log_dir = std::string("Test_Logs");

		std::string logs = "Test_Logs_"+ timestmp;
		std::string source_path_collision = std::string(ExePath_t() + "\\Scripts\\" + Scrpits + "\\");
		std::string destination_path_collision = std::string(ExePath_t() + "\\Test_Logs\\" + logs + "\\" + Scrpits);

		if (CreateDirectory((simulator_log_dir).c_str(), NULL))
		{
			std::cout << "- Create Test log directory " << simulator_log_dir << std::endl;
		}
		else
		{
			print_color_message_t("- Log directory " + simulator_log_dir + " already exists \n", 14);

		}
		std::string Logs_Path = std::string("Test_Logs\\" + logs );
		if (CreateDirectory((Logs_Path).c_str(), NULL))
		{
			std::cout << "-    Create Test log directory " << logs << std::endl;
		}
		else
		{
			print_color_message_t("-    Log directory " + Logs_Path + " already exists \n", 14);

		}

		std::string Logs_Path_current = std::string("Test_Logs\\" + logs + "\\" + Scrpits);
		if (CreateDirectory((Logs_Path_current).c_str(), NULL))
		{
			std::cout << "-    Create Test log directory " << Scrpits << std::endl;
		}
		else
		{
			print_color_message_t("-    Log directory " + Logs_Path_current + " already exists \n", 14);

		}

		bool copy3 = CopyFile((source_path_collision + "\\" + Scrpits + ".py").c_str(),	(destination_path_collision + "\\" + Scrpits + ".py").c_str(), 0);

		std::cout << "-    Copy script:" + Scrpits + ".py" << std::endl;

		if (!copy3) {
			print_color_message_t("-Error while copying python scripts\n", 12);
			print_color_message_t(source_path_collision + "\n", 12);
			print_color_message_t(source_path_collision + "\n", 12);
		}
		return Logs_Path_current;
	}
	
	void accelerate(double *velocity, double acc, double Max) {
		*velocity = *velocity + acc;
		if (*velocity > Max) {
			*velocity = Max;
		}
	}

	void decelerate(double *velocity, double acc) {
		*velocity = *velocity - acc;
		if (*velocity < 0) {
			*velocity = 0;
		}
	}

	void store_2d_field(Water_Waves_Kinematics *enviromental_elements, std::string log_dir_field, int stamp) {
		if (enviromental_elements->get_x_segments_2d() != 0 && enviromental_elements->get_y_segments_2d() != 0) {
			std::fstream element_field;
			element_field.open(log_dir_field + "\\2d_surface_waves_" + to_string(stamp) + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
			for (std::vector<ENVIROMENTAL_SURFACE_WATER_FIELD*>::iterator it = std::begin(enviromental_elements->FOM_table_surface_vess); it != std::end(enviromental_elements->FOM_table_surface_vess); ++it) {
				element_field << (*it)->get_2d_square()->getPointA_x() << " " << (*it)->get_2d_square()->getPointA_y() << " "
					<< (*it)->get_2d_square()->getPointB_x() << " " << (*it)->get_2d_square()->getPointB_y() << " "
					<< (*it)->get_2d_square()->getPointC_x() << " " << (*it)->get_2d_square()->getPointC_y() << " "
					<< (*it)->get_2d_square()->getPointD_x() << " " << (*it)->get_2d_square()->getPointD_y() << " "
					<< (*it)->get_WaterSurfaceSE_wave_frequency() << " " << (*it)->get_WaterSurfaceSE_wave_direction() << " " << (*it)->get_WaterSurfaceSE_wave_height() << "\n";
			}
			element_field << enviromental_elements->get_x_segments_2d() << " " << enviromental_elements->get_y_segments_2d() << "\n";
			element_field.close();
		}
	}

	void store_3d_field(Water_Waves_Kinematics *enviromental_elements, std::string log_dir_field, int stamp) {
		if (enviromental_elements->get_x_segments_3d() != 0 && enviromental_elements->get_y_segments_3d() != 0 && enviromental_elements->get_z_segments_3d() != 0) {
			std::fstream element_field;
			element_field.open(log_dir_field + "\\3d_current_waves_" + to_string(stamp) + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
			for (std::vector<ENVIROMENTAL_CURRENT_WATER_FIELD*>::iterator it = std::begin(enviromental_elements->FOM_table_subwater_vess); it != std::end(enviromental_elements->FOM_table_subwater_vess); ++it) {
				element_field
					<< (*it)->get_3d_square()->getPointA_x() << " " << (*it)->get_3d_square()->getPointA_y() << " " << (*it)->get_3d_square()->getPointA_z() << " "
					<< (*it)->get_3d_square()->getPointB_x() << " " << (*it)->get_3d_square()->getPointB_y() << " " << (*it)->get_3d_square()->getPointB_z() << " "
					<< (*it)->get_3d_square()->getPointC_x() << " " << (*it)->get_3d_square()->getPointC_y() << " " << (*it)->get_3d_square()->getPointC_z() << " "
					<< (*it)->get_3d_square()->getPointD_x() << " " << (*it)->get_3d_square()->getPointD_y() << " " << (*it)->get_3d_square()->getPointD_z() << " "
					<< (*it)->get_3d_square()->getPointE_x() << " " << (*it)->get_3d_square()->getPointE_y() << " " << (*it)->get_3d_square()->getPointE_z() << " "
					<< (*it)->get_3d_square()->getPointF_x() << " " << (*it)->get_3d_square()->getPointF_y() << " " << (*it)->get_3d_square()->getPointF_z() << " "
					<< (*it)->get_3d_square()->getPointG_x() << " " << (*it)->get_3d_square()->getPointG_y() << " " << (*it)->get_3d_square()->getPointG_z() << " "
					<< (*it)->get_3d_square()->getPointH_x() << " " << (*it)->get_3d_square()->getPointH_y() << " " << (*it)->get_3d_square()->getPointH_z() << " "
					<< (*it)->get_SubWater_wave_intensity() << " " << (*it)->get_SubWater_wave_direction() << " " << (*it)->get_SubWater_wave_height() << "\n";
			}
			element_field << enviromental_elements->get_x_segments_3d() << " " << enviromental_elements->get_y_segments_3d() << " " << enviromental_elements->get_z_segments_3d() << "\n";
			element_field.close();
		}
	}

	double angle_balancing_equalizer(double current_x, double current_y, double des_current_x, double des_current_y,double theta_horizontal, double angular_velocity, double linear_velocity) {
		double theta_left;
		double theta_right;
		double x_left, y_left;
		double x_right, y_right;
		double tmp;
		double des_theta_horizontal = angle_between_2d_points(current_x, current_y, des_current_x, des_current_y);

		x_left = current_x;
		y_left = current_y;

		x_right = current_x;
		y_right = current_y;

		theta_left = theta_horizontal;
		theta_right = theta_horizontal;

		if (std::abs(des_theta_horizontal - theta_horizontal) > angular_velocity) {
			double theta_turned = theta_left - angular_velocity;
			double theta_turned_norm_left = angle_degree_normalization(theta_turned);
			move_to_direction(x_left, y_left, linear_velocity, theta_turned_norm_left);

			theta_turned = theta_right + angular_velocity;
			double theta_turned_norm_rigth = angle_degree_normalization(theta_turned);
			move_to_direction(x_right, y_right, linear_velocity, theta_turned_norm_rigth);

			double distance_from_left = point_distance(x_left, y_left, des_current_x, des_current_y);
			double distance_from_right = point_distance(x_right, y_right, des_current_x, des_current_y);

			if (distance_from_left < distance_from_right) {
				tmp = (theta_turned_norm_left);
			}
			else {
				tmp = (theta_turned_norm_rigth);
			}
		}
		else {
			tmp = des_theta_horizontal;
		}
		return tmp;
	}

	double speed_balancing_equalizer(double &acceleration, double &deceleration, double max_acceleration, double max_deceleration,double x, double y, double z,double x_t, double y_t, double z_t, double theta_h, double theta_v, double theta_th, double theta_tv,double speed, std::string type) {


		double dist_curr_to_target = point_distance_3d(x, y, z, x_t, y_t, z_t);
		int velocity_status = 0;

		if (type == "SUB_ROV") {
			double angle_deviation_hor = fabs(theta_h - theta_th);
			double angle_deviation_ver = fabs(theta_v - theta_tv);

			/*velocity_status = check_acceleration_deceleration(
				acceleration, deceleration, max_acceleration, max_deceleration,
				dist_curr_to_target, speed, angle_deviation_hor, angle_deviation_ver);*/
		}
		else {
			double angle_deviation = fabs(theta_h - theta_th);

			/*velocity_status = check_acceleration_deceleration(
				acceleration, deceleration, max_acceleration, max_deceleration,
				dist_curr_to_target, speed, angle_deviation, 0);*/
		}
		double new_velocity = speed;
		if (velocity_status == 0) {
			accelerate(&new_velocity, acceleration, max_acceleration);
		}
		else {
			decelerate(&new_velocity, deceleration);
		}
		return new_velocity;
	}

}
#endif