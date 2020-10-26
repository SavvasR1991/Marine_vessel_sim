#pragma once
#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "Sector.h"
#include "Geometry_Functions.h"
#include "waterSurfaceStateRepository.h"

#define PI 3.14159265358979
#define NO_ELEMENT		0
#define AIRCOLUMN		1
#define LAND			2
#define WATERCOLUMN		4
#define WATERSURFACE	8

enum VESSEL_STATUS {
	ACTIVE = 'A',
	DESTROYED = 'D',
	ERROR_VESSEL = 'E',
	IMMOBILZED = 'I'
};

enum EVENT_MESSAGE {
	TARGET_INCOMING,
	TASK_EXECUTION,
	NO_MESSAGE,
	ERROR_EVENT
};

enum JOB {
	PATROLING = 'P',
	VANGUARED = 'V',
	RESET = 'R',
	INSPECTION = 'I',
	SHADOWING = 'S',
	LOCK = 'L'
};

/****************** VESSEL INFORMATION STATUS *********************/
class TEAM_JOB_STATUS {
	public:
		~TEAM_JOB_STATUS() {
			delete this->areaSector;
		}
		char node_jobs_status;
		std::string name;
		std::string type;

		double current_latitude;
		double current_longitude;
		double current_Height;

		double deploy_latitude;
		double deploy_longitude;
		double deploy_Height;


		double reference_angle_horizontal;
		double reference_angle_vertical;

		Sector *areaSector;

		bool reset_mode_on;
};

/****************** USER INFORMATION DATA *************************/
class USER_INIT_DATA {
public:
	int uxv_num;
	int uxv_subwater;
	int uxv_surface;
	int ship_id;

	double refLatitude = DtDeg2Rad(35.699760);
	double refLongitude = DtDeg2Rad(-121.326577);
	double refHeight = 0;

	double ship_range = 100;
	double uxv_subwater_sensor_range = 100;
	double uxv_surface_sensor_range = 100;

	double uxv_sensor_depth_range = 100;

	double uxv_subwater_length = 4;
	double uxv_subwater_width = 4;
	double uxv_subwater_heigth = 2;
	double angle_subwater_speed = 20;
	double ACCELERATION_subwater = 3;
	double DECELERATION_subwater = 3;
	double MAXIMUM_SPEED_subwater = 15;
	double uxv_subwater_mass;

	double uxv_surface_length = 4;
	double uxv_surface_width = 4;
	double uxv_surface_heigth = 2;
	double angle_surface_speed = 20;
	double ACCELERATION_surface = 3;
	double DECELERATION_surface = 3;
	double MAXIMUM_SPEED_surface = 15;
	double uxv_surface_mass;

	double MAXIMUM_REVERSE_SPEED = 10;
};

/****************** TEAM INFORMATION DATA *************************/
class TEAM_INIT_DATA {
	public:
		int uxv_num;
		int uxv_subwater;
		int uxv_surface;

		double uxv_length_sur;
		double uxv_width_sur;
		double uxv_heigth_sur;

		double uxv_length_sub;
		double uxv_width_sub;
		double uxv_heigth_sub;

		double refLatitude;
		double refLongitude;
		double refHeight;

		double uxv_sensor_range_sur;
		double uxv_sensor_range_sub;
		double uxv_subwater_mass;
		double uxv_surface_mass;

		double uxv_sensor_depth_range;

		double angle_speed_sur;
		double ACCELERATION_sur;					//sensor speed
		double MAXIMUM_SPEED_sur;					//sensor speed
		double DECELERATION_sur;					//sensor speed

		double angle_speed_sub;
		double ACCELERATION_sub;					//sensor speed
		double MAXIMUM_SPEED_sub;					//sensor speed
		double DECELERATION_sub;					//sensor speed
		double MAXIMUM_REVERSE_SPEED;

		double ship_range;
};

/****************** VESSEL INFORMATION DATA ***********************/
class VESSEL_INIT_DATA {
	public:
		std::string name;
		std::string type;
		std::string log_dir;
		int team_id;
		int id_type;

		double length;
		double width;
		double height;
		double mass;

		double refLatitude;
		double refLongitude;
		double refHeight;

		double deploy_latitude;
		double deploy_longitude;

		double sensor_range;
		double sensor_depth_range;

		double uxv_speed;
		double angle_speed;

		double acceleration;
		double deceleration;
		double maximum_speed;
		double maximum_reverse_speed;


		double maximum_depth;
		Sector* sector;
};

/****************** EVENT INFORMATION STATUS **********************/

class FOM_EVENT {
private:
	bool incoming_event_message;
	double x_dis;
	double y_dis;
	double z_dis;
	double angle_hor_dis;
	double angle_ver_dis;
	double mass;
	double velocity;

public:
	FOM_EVENT() {
		this->incoming_event_message = false;
		this->x_dis = 0.0;
		this->y_dis = 0.0;
		this->z_dis = 0.0;
		this->angle_hor_dis = 0.0;
		this->angle_ver_dis = 0.0;
		this->mass = 0.0;
		this->velocity = 0.0;
	}

	void fill_data(FOM_EVENT *new_data) {
		this->incoming_event_message = new_data->getEvent();
		this->x_dis = new_data->get_x_dis();
		this->y_dis = new_data->get_y_dis();
		this->z_dis = new_data->get_z_dis();
		this->angle_hor_dis = new_data->get_angle_hor_dis();
		this->angle_ver_dis = new_data->get_angle_ver_dis();
		this->mass = new_data->get_mass();
		this->velocity = new_data->get_velocity();
	}

	void cleanFOM_evaluator() {
		this->incoming_event_message = false;
		this->x_dis = 0.0;
		this->y_dis = 0.0;
		this->z_dis = 0.0;
		this->angle_hor_dis = 0.0;
		this->angle_ver_dis = 0.0;
		this->mass = 0.0;
		this->velocity = 0.0;

	}
	void setEvent(bool income) {
		this->incoming_event_message = income;
	}
	void set_x_dis(double income) {
		this->x_dis = income;
	}
	void set_y_dis(double income) {
		this->y_dis = income;
	}
	void set_z_dis(double income) {
		this->z_dis = income;
	}
	void set_angle_hor_dis(double income) {
		this->angle_hor_dis = income;
	}
	void set_angle_ver_dis(double income) {
		this->angle_ver_dis = income;
	}

	void set_incoming_event_message() {
		this->incoming_event_message = true;
	}

	void set_mass(double mass) {
		this->mass = mass;
	}

	void set_velocity(double vel) {
		this->velocity = vel;
	}


	bool getEvent() {
		return this->incoming_event_message;
	}
	double get_x_dis() {
		return this->x_dis;
	}
	double get_y_dis() {
		return this->y_dis;
	}
	double get_z_dis() {
		return this->z_dis;
	}
	double get_angle_hor_dis() {
		return this->angle_hor_dis;
	}
	double get_angle_ver_dis() {
		return this->angle_ver_dis;
	}

	double get_mass() {
		return this->mass;
	}

	double get_velocity() {
		return this->velocity;
	}
};


class EVENT {
private:
	EVENT_MESSAGE event_message;
	JOB job;
	double target_refLatitude;
	double target_refLongitude;

public:
	void setEvent(EVENT_MESSAGE ev) {
		this->event_message = ev;
	}
	void setJob(JOB job) {
		this->job = job;
	}
	EVENT_MESSAGE getEvent() {
		return this->event_message;
	}
	JOB getJob() {
		return this->job;
	}
	void clear_event_receiver() {
		 this->event_message = EVENT_MESSAGE::NO_MESSAGE;
		 this->job = JOB::PATROLING;
	}
	EVENT() {
		std::cout << " - Event receiver" << std::endl; 
	}
	~EVENT() {
		std::cout << "Event receiver Deleted" << std::endl;
	}
};

/****************** VESSEL KINIMATICS STATUS **********************/
class VESSEL_KINEMATICS {
private:

	double current_Longitude;
	double current_Latitude;
	double current_Height;

	double destination_Longitude;
	double destination_Latitude;
	double destination_Height;

	double target_theta_horizontal;
	double target_theta_vertical;

	double current_theta_horizontal;
	double current_theta_vertical;

public:
	void set_current_xyz(double x, double y, double z) {
		this->current_Latitude = x;
		this->current_Longitude = y;
		this->current_Height = z;
	}
	void set_current_x(double x) {
		this->current_Latitude = x;
	}
	void set_current_y(double y) {
		this->current_Longitude = y;
	}
	void set_current_z(double z) {
		this->current_Height = z;
	}

	void set_destination_xyz(double x, double y, double z) {
		this->destination_Latitude = x;
		this->destination_Longitude = y;
		this->destination_Height = z;
	}
	void set_destination_x(double x) {
		this->destination_Latitude = x;
	}
	void set_destination_y(double y) {
		this->destination_Longitude = y;
	}
	void set_destination_z(double z) {
		this->destination_Height = z;
	}

	void set_current_theta_horizontal(double theta_x) {
		this->current_theta_horizontal = theta_x;
	}
	void set_current_theta_vertical(double theta_x) {
		this->current_theta_vertical = theta_x;
	}

	void set_destination_theta_horizontal(double theta_x) {
		this->target_theta_horizontal = theta_x;
	}
	void set_destination_theta_vertical(double theta_x) {
		this->target_theta_vertical = theta_x;
	}

	double get_current_x(){ return this->current_Latitude; }
	double get_current_y() { return this->current_Longitude; }
	double get_current_z() { return this->current_Height; }

	double get_destination_x() { return this->destination_Latitude; }
	double get_destination_y() { return this->destination_Longitude; }
	double get_destination_z() { return this->destination_Height; }

	double get_current_theta_horizontal() { return this->current_theta_horizontal; }
	double get_current_theta_vertical() { return this->current_theta_vertical; }
	double get_destination_theta_horizontal() { return this->target_theta_horizontal; }
	double get_destination_theta_vertical() { return this->target_theta_vertical; }
};


class ENVIROMENTAL_SURFACE_WATER_FIELD {
private:
	Square_2d* FOM_table_surface_vess;
	int block_id;
	DtFloat64 WaterSurfaceSE_wave_frequency;
	DtFloat64 WaterSurfaceSE_wave_direction;
	DtFloat64 WaterSurfaceSE_wave_height;
public:
	ENVIROMENTAL_SURFACE_WATER_FIELD(Square_2d* field, DtFloat64 fre, DtFloat64 dir, DtFloat64 hei, int id) {
		this->FOM_table_surface_vess = field;
		this->block_id = id;
		this->WaterSurfaceSE_wave_direction = dir;
		this->WaterSurfaceSE_wave_frequency = fre;
		this->WaterSurfaceSE_wave_height = hei;
	}
	void set_id(int input) {
		this->block_id = input;
	}
	void set_2d_square(Point a, Point b, Point c, Point d) {
		this->FOM_table_surface_vess = new Square_2d(a, b, c, d);
	}
	void set_WaterSurfaceSE_wave_frequency(DtFloat64 input) {
		this->WaterSurfaceSE_wave_frequency = input;
	}
	void set_WaterSurfaceSE_wave_direction(DtFloat64 input) {
		this->WaterSurfaceSE_wave_direction = input;
	}
	void set_WaterSurfaceSE_wave_height(DtFloat64 input) {
		this->WaterSurfaceSE_wave_height = input;
	}

	Square_2d* get_2d_square() {
		return this->FOM_table_surface_vess;
	}
	DtFloat64 get_WaterSurfaceSE_wave_frequency() {
		return this->WaterSurfaceSE_wave_frequency;
	}
	DtFloat64 get_WaterSurfaceSE_wave_direction() {
		return this->WaterSurfaceSE_wave_direction;
	}
	DtFloat64 get_WaterSurfaceSE_wave_height() {
		return this->WaterSurfaceSE_wave_height;
	}
};

class ENVIROMENTAL_CURRENT_WATER_FIELD {
private:
	Square_3d* FOM_table_subwater_vess;
	int block_id;
	DtFloat64 SubWater_wave_intensity;
	DtFloat64 SubWater_wave_direction;
	DtFloat64 SubWater_wave_height;
public:
	ENVIROMENTAL_CURRENT_WATER_FIELD(Square_3d* field, DtFloat64 inter, DtFloat64 dir, DtFloat64 hei, int id) {
		this->FOM_table_subwater_vess = field;
		this->block_id = id;
		this->SubWater_wave_direction = dir;
		this->SubWater_wave_intensity = inter;
		this->SubWater_wave_height = hei;
	}
	void set_id(int input) {
		this->block_id = input;
	}
	void set_3d_square(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h) {
		this->FOM_table_subwater_vess = new Square_3d(a, b, c, d, e, f, g, h);
	}
	void set_SubWater_wave_intensity(DtFloat64 input) {
		this->SubWater_wave_intensity = input;
	}
	void set_SubWater_wave_direction(DtFloat64 input) {
		this->SubWater_wave_direction = input;
	}
	void set_SubWater_wave_height(DtFloat64 input) {
		this->SubWater_wave_height = input;
	}

	Square_3d* get_3d_square() {
		return this->FOM_table_subwater_vess;
	}
	DtFloat64 get_SubWater_wave_intensity() {
		return this->SubWater_wave_intensity;
	}
	DtFloat64 get_SubWater_wave_direction() {
		return this->SubWater_wave_direction;
	}
	DtFloat64 get_SubWater_wave_height() {
		return this->SubWater_wave_height;
	}

};
#endif