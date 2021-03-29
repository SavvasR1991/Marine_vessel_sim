#pragma once
#ifndef WATER_WAVES_KINEMATICS_T_H
#define WATER_WAVES_KINEMATICS_T_H

#include "Helper_Header.h"


class Water_Waves_Kinematics_T {

public:
		
	bool water_waves_kinematics_test_1(std::map<std::string, double> data, std::string Logs_Path,int stamp, Water_Waves_Kinematics* detector, FOM_EVENT *event) {
		double vessel_x = data["vessel_x"];
		double vessel_y = data["vessel_y"];
		double vessel_z = data["vessel_z"];
		double vessel_angle = data["vessel_angle"];
		double vessel_velocity = data["vessel_velocity"];
		double vessel_angle_velocity = data["vessel_angle_velocity"];
		double target_x = data["target_x"];
		double target_y = data["target_y"];
		double vessel_radius = data["vessel_radius"];
		double NW_X = data["NW_X"];
		double NW_Y = data["NW_Y"];
		double NW_Z = data["NW_Z"];
		double SE_X = data["SE_X"];
		double SE_Y = data["SE_Y"];
		double SE_Z = data["SE_Z"];
		double ii = data["I"];
		double jj = data["J"];
		double kk = data["K"];
		double frequency = data["frequency"];
		double direction = data["direction"];
		double intencity = data["intencity"];
		double height = data["height"];
		double B = data["Be"];
		double L = data["Le"];
		double T = data["Height_vessel"];
		double mass = data["mass"];
		double possibility = data["possibility"];
		std::string type = (data["type"] == 0.0) ? "SURFACE" : "SUBWATER";
		std::string fieldpath = Logs_Path + "\\" + "Logs" + to_string(stamp) + ".txt";
		std::string fieldpathwave = Logs_Path + "\\" + "Wave_hits" + to_string(stamp) + ".txt";
		ofstream logs(fieldpath);
		ofstream wave(fieldpathwave);
		int counter = 0;
		int iSecret;

		srand(time(NULL));

		detector->created_2d_Water_Surface_field_T(NW_X, NW_Y, SE_X, SE_Y, frequency, direction, height, ii, jj);
		while (counter <= 1500) {
			iSecret = rand() % 10 + 1;
			if (10-possibility < iSecret) {
				detector->set_enviromental_disruption_for_point("test",event, vessel_x, vessel_y, vessel_z,vessel_angle, vessel_angle_velocity,vessel_velocity, vessel_angle_velocity, vessel_angle_velocity,type, B, L, T, mass, counter, B);
				vessel_angle = event->get_angle_hor_dis();
				wave << counter << "\n";
			}
			else {
				wave << "0\n";
			}
			move_to_direction(vessel_x, vessel_y, vessel_velocity, vessel_angle);
			logs << (vessel_x) << " " << (vessel_y) << " " << vessel_z << "\n";
			counter++;
			vessel_angle = angle_balancing_equalizer(vessel_x, vessel_y, target_x, target_y,vessel_angle, vessel_angle_velocity, vessel_velocity);
			if (circles_intersection(vessel_x, vessel_y, target_x, target_y, 5, 5))	{break;}
			if (counter > 1000) {possibility = 0;}
		}
		logs << (target_x) << " " << (target_y) << " " << vessel_z << "\n";
		logs.close();
		wave.close();
		store_2d_field(detector, Logs_Path, stamp);
		return true;
	}

	bool water_waves_kinematics_test_2(std::map<std::string, double> data, std::string Logs_Path, int stamp, Water_Waves_Kinematics* detector, FOM_EVENT *event) {
		double vessel_x = data["vessel_x"];
		double vessel_y = data["vessel_y"];
		double vessel_z = data["vessel_z"];
		double vessel_angle = data["vessel_angle"];
		double vessel_velocity = data["vessel_velocity"];
		double vessel_angle_velocity = data["vessel_angle_velocity"];
		double target_x = data["target_x"];
		double target_y = data["target_y"];
		double vessel_radius = data["vessel_radius"];
		double NW_X = data["NW_X"];
		double NW_Y = data["NW_Y"];
		double NW_Z = data["NW_Z"];
		double SE_X = data["SE_X"];
		double SE_Y = data["SE_Y"];
		double SE_Z = data["SE_Z"];
		double ii = data["I"];
		double jj = data["J"];
		double kk = data["K"];
		double frequency = data["frequency"];
		double direction = data["direction"];
		double intencity = data["intencity"];
		double temperature = data["temperature"];
		double salinity = data["salinity"];
		double atm_pressure = data["atm_pressure"];
		double height = data["height"];
		double B = data["Be"];
		double L = data["Le"];
		double T = data["Height_vessel"];
		double mass = data["mass"];
		double possibility = data["possibility"];
		std::string type = (data["type"] == 0.0) ? "SURFACE" : "SUBWATER";
		std::string fieldpath = Logs_Path + "\\" + "Logs" + to_string(stamp) + "_subwater.txt";
		std::string fieldpathwave = Logs_Path + "\\" + "Wave_hits" + to_string(stamp) + "_subwater.txt";
		ofstream logs(fieldpath);
		ofstream wave(fieldpathwave);
		int counter = 0;
		int iSecret;

		srand(time(NULL));
		detector->created_3d_Water_Current_field_T(NW_X, NW_Y, NW_Z, SE_X, SE_Y, SE_Z, intencity, direction, salinity, temperature, ii, jj, kk);
		while (counter <= 1500) {
			iSecret = rand() % 10 + 1;
			if (10 - possibility < iSecret) {
				detector->set_enviromental_disruption_for_point("test", event, vessel_x, vessel_y, vessel_z, vessel_angle, vessel_angle_velocity, vessel_velocity, vessel_angle_velocity, vessel_angle_velocity, type, B, L, T, mass, B, counter);
				vessel_angle = event->get_angle_hor_dis();
				wave << counter << "\n";
			}
			else {
				wave << "0\n";
			}
			move_to_direction(vessel_x, vessel_y, vessel_velocity, vessel_angle);
			logs << (vessel_x) << " " << (vessel_y) << " " << vessel_z << "\n";
			counter++;
			vessel_angle = angle_balancing_equalizer(vessel_x, vessel_y, target_x, target_y, vessel_angle, vessel_angle_velocity, vessel_velocity);
			if (circles_intersection(vessel_x, vessel_y, target_x, target_y, 5, 5)) { break; }
			if (counter > 1000) { possibility = 0; }
		}
		logs << (target_x) << " " << (target_y) << " " << vessel_z << "\n";
		logs.close();
		wave.close();
		store_3d_field(detector, Logs_Path, stamp);
		return true;
	}

};
#endif