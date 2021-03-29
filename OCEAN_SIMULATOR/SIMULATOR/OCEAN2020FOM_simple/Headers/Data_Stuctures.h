#pragma once
#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "Sector.h"
#include "Geometry_Functions.h"
#include "Data_Constant_Values.h"
#include "waterSurfaceStateRepository.h"

class SHADOWING_TEAM_DATA {
private:
	bool vangared_leader;
	bool available;

	int id;
	int shadow_id;
	int direction;
	double distance;
	double x;
	double y;
	double z;
	double x_target;
	double y_target;
	double z_target;
	double theta_hor_target;
	double velocity_target;
	double radar;

	double radius;
	double xBeforeRotation;
	double yBeforeRotation;
	char job;
	char comms;

	std::string type;
	std::string vessel_name;
	std::string vessel_name_leader;

public:
	SHADOWING_TEAM_DATA(double distance, double radar, std::string vessel_name, std::string type, std::string vessel_name_leader, bool vangared_leader, int id, double radius, int shadow_id, char job, char comm) {
		if (comm == 'y') {
			std::cout << "----- Create shadow team node : " << vessel_name << std::endl;
		}
		this->comms = comm;
		this->distance = distance;
		this->vessel_name = vessel_name;
		this->vangared_leader = vangared_leader;
		this->vessel_name_leader = vessel_name_leader;
		this->id = id;
		this->available = true;
		this->radius = radius;
		this->shadow_id = shadow_id;
		this->type = type;
		this->job = job;
		this->radar = radar;
	}
	SHADOWING_TEAM_DATA(double distance, double radar, std::string vessel_name, std::string type, std::string vessel_name_leader,bool vangared_leader, int id, double radius, int shadow_id, char job, bool no_comm) {
		this->distance = distance;
		this->vessel_name = vessel_name;
		this->vangared_leader = vangared_leader;
		this->vessel_name_leader = vessel_name_leader;
		this->id = id;
		this->available = true;
		this->radius = radius;
		this->shadow_id = shadow_id;
		this->type = type;
		this->job = job;
		this->radar = radar;
		if (no_comm) {
			comms = 'y';
		}
		else {
			comms = 'n';
		}
	}
	~SHADOWING_TEAM_DATA() {
		if (comms == 'y') {
			std::cout << "------ Shadow team delete part: " << this->vessel_name << std::endl;
		}
	}

	void update_shadow_member(double x, double y, double z, double x_target, double y_target, double z_target, double theta_hor_t, double vel_t)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->x_target = x_target;
		this->y_target = y_target;
		this->z_target = z_target;
		this->theta_hor_target = theta_hor_t;
		this->velocity_target = vel_t;
		this->distance = point_distance_3d(x,y,z,x_target, y_target, z_target);
	}
	
	void update_shadow_member_target(double x_target, double y_target, double z_target)
	{
		this->x_target = x_target;
		this->y_target = y_target;
		this->z_target = z_target;
		this->distance = point_distance_3d(this->x, this->y, this->z, x_target, y_target, z_target);
	}

	void update_shadow_member_coordinates(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void vote_leader(bool avail) {
		this->vangared_leader = avail;
	}

	void set_availability(bool avail) {
		this->available = avail;
	}
	void set_coord_BeforeRotation(double xBeforeRotation, double yBeforeRotation, int direction) {
		this->xBeforeRotation = xBeforeRotation;
		this->yBeforeRotation = yBeforeRotation;
		this->direction = direction;
	}
	void set_vessel_name_leader(std::string name) {
		this->vessel_name_leader = name;

	}
	void set_job(char id) {
		this->job = id;
	}
	void set_Radar(double radar) {
		this->radar = radar;
	}
	void set_id(int id) {
		this->id = id;
	}
	void set_shadow_id(int id) {
		this->shadow_id = id;
	}

	double get_distance() {
		return this->distance;
	}
	double get_X() {
		return this->x;
	}
	double get_Y() {
		return this->y;
	}
	double get_Z() {
		return this->z;
	}
	double get_X_target() {
		return this->x_target;
	}
	double get_Y_target() {
		return this->y_target;
	}
	double get_Z_target() {
		return this->z_target;
	}
	double get_radius() {
		return this->radius;
	}
	double get_Radar_Range() { return this->radar; }
	double get_coord_X_BeforeRotation() {
		return this->xBeforeRotation;
	}
	double get_coord_Y_BeforeRotation() {
		return this->yBeforeRotation;
	}
	double get_Theta_Hor_target() {
		return theta_hor_target;
	}
	double get_Velocity_target() {
		return velocity_target;
	}
	int get_id() {
		return this->id;
	}
	int get_direction() {
		return this->direction;
	}
	int get_shadow_id() {
		return this->shadow_id;
	}
	std::string get_vessel_name_leader() {
		return this->vessel_name_leader;
	}
	std::string get_name() {
		return this->vessel_name;
	}
	std::string get_type() {
		return this->type;
	}
	char get_job() {
		return this->job;
	}
	bool is_leader() {
		return this->vangared_leader;
	}
	bool is_available() {
		return this->available;
	}
	
	void print_voting_shadow_team_summarize() {
		std::cout << "---- " << this->get_name() << ": Team (" << this->get_id() << "), radius = " << this->get_radius() << " ,distance:" << this->get_distance() << " " << " -> avail: ";
		if (this->is_available()) {
			std::cout << " Yes , Leader: " << this->get_vessel_name_leader();
		}
		else {
			std::cout << " No , Leader: " << this->get_vessel_name_leader();
		}
		std::cout << " (Tx:" << this->get_X_target() << " ,Ty:" << this->get_Y_target() << ") <- (" << this->get_X() << "," << this->get_Y() << ")\n";
	}
};

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
		bool oversight_mode_on;
		bool out_of_area;

};

class TEAM_INIT_DATA {
	public:
		int uxv_num;
		int uxv_subwater;
		int uxv_surface;
		int targets_num;
		int ship_shadowing_team;
		int ship_id;
		int Ship_Activated;

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
		double MAX_SUBMERSION_SPEED;

		double avoid_distance;
		double safe_distance;

		double Vanguared_Distance_sur;
		double Vanguared_Distance_sub;
		double Vanguared_Distance_sub_depth;

		double oversight_timer;
		double ship_range;

		int Naval_Base_Activate;
		double Naval_Base_Activate_degrees_tilt;

		int Jamming_Activate;
		double Jamming_time_start;

		double target_x_1;
		double target_y_1;
		double target_z_1;
		double target_id_1;
		double target_velocity_1;
		double target_angle_1;
		int target_start_time_1;
		int target_is_a_bomb_1;
		int target_turning_point_1_1;
		int target_turning_point_2_1;
		int target_turning_point_3_1;
		int target_turning_point_4_1;
		int target_turning_point_5_1;
		int target_turning_point_6_1;
		int target_turning_point_7_1;
		int target_turning_point_8_1;
		int target_turning_point_9_1;
		int target_turning_point_10_1;
		double target_turning_angle_1;

		double target_x_2;
		double target_y_2;
		double target_z_2;
		double target_id_2;
		double target_velocity_2;
		double target_angle_2;
		int target_start_time_2;
		int target_is_a_bomb_2;
		int target_turning_point_1_2;
		int target_turning_point_2_2;
		int target_turning_point_3_2;
		int target_turning_point_4_2;
		int target_turning_point_5_2;
		int target_turning_point_6_2;
		int target_turning_point_7_2;
		int target_turning_point_8_2;
		int target_turning_point_9_2;
		int target_turning_point_10_2;
		double target_turning_angle_2;

		double target_x_3;
		double target_y_3;
		double target_z_3;
		double target_id_3;
		double target_velocity_3;
		double target_angle_3;
		int target_start_time_3;
		int target_is_a_bomb_3;
		int target_turning_point_1_3;
		int target_turning_point_2_3;
		int target_turning_point_3_3;
		int target_turning_point_4_3;
		int target_turning_point_5_3;
		int target_turning_point_6_3;
		int target_turning_point_7_3;
		int target_turning_point_8_3;
		int target_turning_point_9_3;
		int target_turning_point_10_3;
		double target_turning_angle_3;
};

class VESSEL_INIT_DATA {
	public:
		std::string name;
		std::string type;
		std::string log_dir;
		std::string log_dir_timer;
		std::string log_dir_Kalman_Filter;

		int team_id;
		int id_type;
		double ship_range;

		double length;
		double width;
		double height;
		double mass;

		double refLatitude;
		double refLongitude;
		double refHeight;

		double deploy_latitude_INIT;
		double deploy_longitude_INIT;

		double deploy_latitude;
		double deploy_longitude;

		double sensor_range;
		double sensor_depth_range;

		double uxv_speed;
		double angle_speed;

		double acceleration;
		double deceleration;
		double maximum_speed;
		double maximum_speed_submersion;
		double acceleration_decent;

		double oversight_timer;

		double avoid_distance;
		double safe_distance;

		double vanguard_distance;
		double vanguared_distance_sub;
		double vanguared_Distance_sub_depth;

		double maximum_depth;
		Sector* sector;

		char logs_Kalman;
};

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
	std::string name;

public:
	FOM_EVENT(std::string name) {
		std::cout << "---- FOM Event Evaluator created for "<< name << std::endl;
		this->name = name;
		this->incoming_event_message = false;
		this->x_dis = 0.0;
		this->y_dis = 0.0;
		this->z_dis = 0.0;
		this->angle_hor_dis = 0.0;
		this->angle_ver_dis = 0.0;
		this->mass = 0.0;
		this->velocity = 0.0;
	}
	~FOM_EVENT() {
		std::cout << "---- FOM Event Evaluator deleted" << std::endl;
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

	void print_FOM_Event() {
		cout << "---- FOM EVENT " << this->name << endl;
		cout << "-- x_dis:         " << this->x_dis << endl;
		cout << "-- y_dis:         " << this->y_dis << endl;
		cout << "-- z_dis:         " << this->z_dis << endl;
		cout << "-- angle_hor_dis: " << this->angle_hor_dis << endl;
		cout << "-- angle_ver_dis: " << this->angle_ver_dis << endl;
		cout << "-- mass:		   " << this->mass << endl;
		cout << "-- velocity:      " << this->velocity << endl << endl;
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
	int id;
	double target_Latitude;
	double target_Longitude;
	double target_Height;
	double target_velocity;
	double target_angle;
	double target_radius;
	double bomb;
	std::string vessel_name;
public:
	void setEvent(EVENT_MESSAGE ev) {
		this->event_message = ev;
	}
	void setID(int x) {
		this->id = x;
	}
	void setJob(JOB job) {
		this->job = job;
	}
	void setX(double x) {
		this->target_Latitude = x;
	}
	void setY(double y) {
		this->target_Longitude = y;
	}
	void setZ(double z) {
		this->target_Height = z;
	}
	void setAngle(double angle) {
		this->target_angle = angle;
	
	}void setRadius(double target_radius) {
		this->target_radius = target_radius;
	}
	void setVelocity(double vel) {
		this->target_velocity = vel;
	}

	EVENT_MESSAGE getEvent() {
		return this->event_message;
	}
	JOB getJob() {
		return this->job;
	}
	int getID() {
		return this->id;
	}
	double getX() {
		return this->target_Latitude;
	}
	double getY() {
		return this->target_Longitude;
	}
	double getZ() {
		return this->target_Height;
	}
	double getVelocity() {
		return this->target_velocity;
	}
	double getAngle() {
		return this->target_angle;
	}
	double getRadius() {
		return this->target_radius;
	}

	void clear_event_receiver() {
		 this->event_message = EVENT_MESSAGE::NO_MESSAGE;
		 this->job = JOB::NONE;
		 this->target_Latitude = 0;
		 this->target_Longitude = 0;
		 this->target_Height = 0;
		 this->target_velocity = 0;
		 this->target_angle = 0;
	}

	EVENT(EVENT_MESSAGE event,JOB job, int id,double x, double y, double z,double angle, double vel, double radius, std::string vessel) {
		this->id =id;
		this->event_message = event;
		this->job = job;
		this->target_Latitude = x;
		this->target_Longitude = y;
		this->target_Height = z;
		this->target_velocity = vel;
		this->target_angle = angle;
		this->vessel_name = vessel;
		this->target_radius = radius;
	}
	~EVENT() {
	}
};

class VESSEL_CHARACTERISTICS {
private:
	std::string type;
	std::string name;
	double scanning_radius;
	double depth_radius;
	double height;
	double length;
	double width;
	double mass;
	double vessel_geo_area;

public:
	VESSEL_CHARACTERISTICS() {
		std::cout << "---- Vessel design created" << std::endl;
	}
	~VESSEL_CHARACTERISTICS() {
		std::cout << "---- Vessel design deleted" << std::endl;
	}
	void set_current_dimensions(double height, double length, double width, double mass,double scan, double depth, std::string type, std::string name) {
		this->height = height;
		this->length = length;
		this->width = width;
		this->mass = mass;
		this->type = type;
		this->name = name;
		this->scanning_radius = scan;
		this->depth_radius = depth;

		if (width >= length) {
			this->vessel_geo_area = (width);
		}
		else {
			this->vessel_geo_area = (length);
		}
	}
	double get_height() { return this->height; }
	double get_length() { return this->length; }
	double get_width() { return this->width; }
	double get_mass() { return this->mass; }
	double get_scanning_radius() { return this->scanning_radius; }
	double get_area_radius() { return this->vessel_geo_area; }
	double get_depth_radius() { return this->depth_radius; }
	std::string get_type() { return this->type; }
	std::string get_name() { return this->name; }
	void print_vessel_characteristics(){
		cout << "-- Print vessel chatacteristics:  Name:" << this->name	<< " type:" << this->type << " area:" << this->vessel_geo_area << endl;
	}
};

class VESSEL_MOTION_VALUES {
private:
	double acceleration;
	double deceleration;
	double Max_acceleration;
	double Max_deceleration;
	double Max_speed;
	double Max_reverse_speed;
	double Max_angle_speed;
	double linear_velocity;
	double linear_velocity_x;
	double linear_velocity_y;
	double linear_velocity_z;
	double acceleration_x;
	double acceleration_y;
	double acceleration_z;
	double acceleration_decent;
	int velocity_status;
	int vertical_direction;

public:
	VESSEL_MOTION_VALUES() {
		std::cout << "---- Motion Evaluator created" << std::endl;
	}
	~VESSEL_MOTION_VALUES() {
		std::cout << "---- Motion Evaluator deleted" << std::endl;
	}

	void set_current_values(double Max_acceleration, double Max_deceleration, double Max_angle_speed, double Max_speed, double Max_reverse_speed, double linear_velocity, double acceleration_decent) {
		this->Max_acceleration = Max_acceleration;
		this->Max_deceleration = Max_deceleration;
		this->Max_angle_speed = Max_angle_speed;
		this->Max_speed = Max_speed;
		this->Max_reverse_speed = Max_reverse_speed;
		this->linear_velocity = linear_velocity;
		this->acceleration_decent = acceleration_decent;
	}
	void set_speed(double v, double phi, double psi, double theta) {
		this->linear_velocity = v;
		this->linear_velocity_x = abs(v * cos(degrees_to_radians(phi)));
		this->linear_velocity_y = abs(v * sin(degrees_to_radians(phi)));
		this->linear_velocity_z = 0.0;
	}
	
	void set_velocity_status(int v) {
		this->velocity_status = v;
	}

	void set_acceleration(double v) {
		this->acceleration = v;
	}
	void set_acceleration_comp_x(double v) {
		this->acceleration_x = v;
	}
	void set_acceleration_comp_y(double v) {
		this->acceleration_y = v;
	}
	void set_acceleration_comp_z(double v) {
		this->acceleration_z = v;

	}

	void set_speed(double v) {
		this->linear_velocity = v;
	}
	void set_speed_comp_x(double v) {
		this->linear_velocity_x = v;
	}
	void set_speed_comp_y(double v) {
		this->linear_velocity_y = v;
	}
	void set_speed_comp_z(double v) {
		this->linear_velocity_z = v;
	}

	void set_acceleration_comp(double v, double phi) {
		this->acceleration_x = abs(v * cos(degrees_to_radians(phi)));
		this->acceleration_y = abs(v * sin(degrees_to_radians(phi)));
		this->acceleration_z = 0.0;
	}
	void set_deceleration(double v) {
		this->deceleration = v;
	}
	void set_deceleration_comp(double v, double phi) {
		this->acceleration_x = -abs(v * cos(degrees_to_radians(phi)));
		this->acceleration_y = -abs(v * sin(degrees_to_radians(phi)));
		this->acceleration_z = 0.0;
	}

	double get_deceleration() { return this->deceleration; }
	double get_Max_acceleration() { return this->Max_acceleration; }
	double get_Max_deceleration() { return this->Max_deceleration; }
	double get_Max_angle_speed() { return this->Max_angle_speed; }
	double get_Max_speed() { return this->Max_speed; }
	double get_Max_reverse_speed() { return this->Max_reverse_speed; }
	double get_speed() { return this->linear_velocity; }
	double get_speed_x() { return this->linear_velocity_x; }
	double get_speed_y() { return this->linear_velocity_y; }
	double get_speed_z() { return this->linear_velocity_z; }
	double get_acceleration() { return this->acceleration; }
	double get_acceleration_x() { return this->acceleration_x; }
	double get_acceleration_y() { return this->acceleration_y; }
	double get_acceleration_z() { return this->acceleration_z; }
	double get_acceleration_decent() { return this->acceleration_decent; }
	int get_velocity_status() { return this->velocity_status; }
};

class VESSEL_KINEMATICS {
private:

	double reference_Longitude;
	double reference_Latitude;
	double reference_Height;

	double deploy_Longitude;
	double deploy_Latitude;
	double deploy_Height;

	double reset_Longitude;
	double reset_Latitude;
	double reset_Height;

	double current_Longitude;
	double current_Latitude;
	double current_Height;

	double destination_Longitude;
	double destination_Latitude;
	double destination_Height;

	double x_safe_point;
	double y_safe_point;
	double z_safe_point;

	double target_theta_horizontal;
	double target_theta_vertical;

	double current_theta_horizontal;
	double current_theta_vertical;

	double reference_theta_horizontal;
	double reference_theta_vertical;

public:
	VESSEL_KINEMATICS() {
		std::cout << "---- Kinematics Evaluator created" << std::endl;
	}
	~VESSEL_KINEMATICS() {
		std::cout << "---- Kinematics Evaluator deleted" << std::endl;
	}
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
	void set_reference_xyz(double x, double y, double z) {
		this->reference_Latitude = x;
		this->reference_Longitude = y;
		this->reference_Height = z;
	}
	void set_reference_z(double z) {
		this->reference_Height = z;
	}
	void set_deploy_xyz(double x, double y, double z) {
		this->deploy_Latitude = x;
		this->deploy_Longitude = y;
		this->deploy_Height = z;
	}
	void set_deploy_z(double z){
		this->deploy_Height = z;
	}
	void set_current_theta_horizontal(double theta_x) {
		this->current_theta_horizontal = theta_x;
	}
	void set_current_theta_vertical(double theta_x) {
		this->current_theta_vertical = theta_x;
	}

	void set_reset_xyz(double x, double y, double z) {
		this->reset_Latitude = x;
		this->reset_Longitude = y;
		this->reset_Height = z;
	}
	void set_destination_theta_horizontal(double theta_x) {
		this->target_theta_horizontal = theta_x;
	}
	void set_destination_theta_vertical(double theta_x) {
		this->target_theta_vertical = theta_x;
	}

	void set_reference_theta_horizontal(double theta_x) {
		this->reference_theta_horizontal = theta_x;
	}
	void set_reference_theta_vertical(double theta_x) {
		this->reference_theta_vertical = theta_x;
	}

	void set_safe_xyz(double x, double y, double z) {
		this->x_safe_point = x;
		this->y_safe_point = y;
		this->z_safe_point = z;
	}

	double get_current_x(){ return this->current_Latitude; }
	double get_current_y() { return this->current_Longitude; }
	double get_current_z() { return this->current_Height; }

	double get_destination_x() { return this->destination_Latitude; }
	double get_destination_y() { return this->destination_Longitude; }
	double get_destination_z() { return this->destination_Height; }

	double get_reference_x() { return this->reference_Latitude; }
	double get_reference_y() { return this->reference_Longitude; }
	double get_reference_z() { return this->reference_Height; }

	double get_deploy_x() { return this->deploy_Latitude; }
	double get_deploy_y() { return this->deploy_Longitude; }
	double get_deploy_z() { return this->deploy_Height; }

	double get_current_theta_horizontal() { return this->current_theta_horizontal; }
	double get_current_theta_vertical() { return this->current_theta_vertical; }
	double get_destination_theta_horizontal() { return this->target_theta_horizontal; }
	double get_destination_theta_vertical() { return this->target_theta_vertical; }
	double get_reference_theta_horizontal() { return this->reference_theta_horizontal; }
	double get_reference_theta_vertical() { return this->reference_theta_vertical; }

	double get_reset_x() { return this->reset_Latitude; }
	double get_reset_y() { return this->reset_Longitude; }
	double get_reset_z() { return this->reset_Height; }

	double get_safe_point_x() { return this->x_safe_point; }
	double get_safe_point_y() { return this->y_safe_point; }
	double get_safe_point_z() { return this->z_safe_point; }

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
	DtFloat64 SubWater_wave_salinity;
	DtFloat64 SubWater_wave_temperature;

public:
	ENVIROMENTAL_CURRENT_WATER_FIELD(Square_3d* field, DtFloat64 inter, DtFloat64 dir, DtFloat64 sal, DtFloat64 temp, DtFloat64 hei, int id) {
		this->FOM_table_subwater_vess = field;
		this->block_id = id;
		this->SubWater_wave_direction = dir;
		this->SubWater_wave_intensity = inter;
		this->SubWater_wave_height = hei;
		this->SubWater_wave_salinity = sal;
		this->SubWater_wave_temperature = temp;
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
	DtFloat64 get_SubWater_wave_temperature() {
		return this->SubWater_wave_temperature;
	}
	DtFloat64 get_SubWater_wave_salinity() {
		return this->SubWater_wave_salinity;
	}
	

};

class TARGET_STATS {
public:
	double x;
	double y;
	double z;
	double vel;
	double ang;
	double radius;
	int id;
	TARGET_STATS(double x, double y, double z, double vel, double ang, double radius, int id) {
		this->x =x;
		this->y=y;
		this->z=z;
		this->vel=vel;
		this->ang=ang;
		this->id=id;
		this->radius = radius;
	}
	void set_xy(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void set_xyx(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class TRANSMITER_DATA {
private:
	double ID;
	DtAntennaPatternType antennaType;
	double MaxGain;
	DtTxRxTypeEnum Type;
	double channelBandwidth;
	double tuning;
	double frequencies; 
	double harmonics;
	double spurios;
	double Position;
	DtRadioSystem modulation;
	DtRadioMajorModulation modulation_major;
	DtAntiJammingTechniqueEnum antijamm;
public:
	TRANSMITER_DATA() {
		std::cout << "---- Radio Transmitter created" << std::endl;
	}
	~TRANSMITER_DATA() {
		std::cout << "---- Radio Transmitter deleted" << std::endl;
	}
	void set_transmitter_attributes(
			double ID,	double antennaType,	double MaxGain,	double Type,double channelBandwidth,
			double tuning,double frequencies,double harmonics,double spurios,double Position,
			double modulation, double modulation_major,	double antijamm	)
	{
		this->ID = ID;
		this->antennaType = static_cast<DtAntennaPatternType>((int)(antennaType));
		this->MaxGain = MaxGain;
		this->Type = static_cast<DtTxRxTypeEnum>((int)(Type)) ;
		this->channelBandwidth = channelBandwidth;
		this->tuning = tuning;
		this->frequencies = frequencies;
		this->spurios = spurios;
		this->Position = Position;
		this->modulation = static_cast<DtRadioSystem>((int)(modulation));
		this->modulation_major = static_cast<DtRadioMajorModulation>((int)(modulation_major));
		this->antijamm = static_cast<DtAntiJammingTechniqueEnum>((int)(antijamm));
	}

	double get_ID() { return this->ID; }
	DtAntennaPatternType get_antennaType() { return this->antennaType; }
	double get_MaxGain() { return this->MaxGain; }
	DtTxRxTypeEnum get_Type() { return this->Type; }
	double get_channelBandwidth() { return this->channelBandwidth; }
	double get_tuning() { return this->tuning; }
	double get_frequencies() { return this->frequencies; }
	double get_harmonics() { return this->harmonics; }
	double get_spurios() { return this->spurios; }
	double get_Position() { return this->Position; }
	DtRadioSystem get_modulation() { return this->modulation; }
	DtRadioMajorModulation get_modulation_major() { return this->modulation_major; }
	DtAntiJammingTechniqueEnum get_antijamm() { return this->antijamm; }

	void print_transmiter_data() {
		cout << "--> id: " << ID << endl;
		cout << "--> Antenna Type: " << print_antennaType() << endl;
		cout << "--> Max Gain: " << MaxGain << " Hz"<<endl;
		cout << "--> Type: " << print_transmitterType() << endl;
		cout << "--> Channel Bandwidth: " << ID << " Hz"<<endl;
		cout << "--> Tuning: " << tuning << endl;
		cout << "--> Frequencies: " << frequencies << " Hz" << endl;
		cout << "--> Modulation: " << print_modulation() << endl;
		cout << "--> Modulation_major: " << print_modulation_major() << endl;
		cout << "--> Antijamm: " << print_antijamming() << endl;
	}
	std::string print_transmitterType() {
		if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_AMCOMM) {
			return "AM COMM";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_AMVOICE) {
			return "AM VOICE";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_ASK) {
			return "ASK";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_CWRADAR) {
			return "CWRADAR";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_DSSS) {
			return "DSSS";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_FHSS) {
			return "FHSS";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_FM) {
			return "FM";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_JAMMER) {
			return "JAMMAR";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_JAMMER_FHSS) {
			return "JAMMER_FHSS";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_NOEPM) {
			return "NOEPM";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_PSK) {
			return "PSK";
		}
		else if (this->Type == DtTxRxTypeEnum::DtTxRxTypeEnum_PULSERADAR) {
			return "PULSERADAR";
		}
		else {
			return "QAM";
		}
	}
	std::string print_antennaType() {
		if (this->Type == DtAntennaPatternType::DtOmniDirectional) {
			return "OmniDirectional";
		}
		else if (this->antennaType == DtAntennaPatternType::DtBeam) {
			return "Beam";
		}
		else {
			return "Spherical Harmonic";
		}
	}
	std::string print_modulation() {
		if (this->modulation == DtRadioSystem::DtCCTT_SINCGARS) {
			return "CCTT_SINCGARS";
		}
		else if (this->modulation == DtRadioSystem::DtEnhancedSINCGARS7_3) {
			return "EnhancedSINCGARS7_3";
		}
		else if (this->modulation == DtRadioSystem::DtEPLRS) {
			return "EPLRS";
		}
		else if (this->modulation == DtRadioSystem::DtGeneric) {
			return "Generic";
		}
		else if (this->modulation == DtRadioSystem::DtHq) {
			return "Hq";
		}
		else if (this->modulation == DtRadioSystem::DtHqII) {
			return "HqII";
		}
		else if (this->modulation == DtRadioSystem::DtHqIIA) {
			return "HqIIA";
		}
		else if (this->modulation == DtRadioSystem::DtJTIDS_MIDS) {
			return "JTIDS_MIDS";
		}
		else if (this->modulation == DtRadioSystem::DtLBandSATCOM) {
			return "LBandSATCOM";
		}
		else if (this->modulation == DtRadioSystem::DtLink11) {
			return "Link11";
		}
		else if (this->modulation == DtRadioSystem::DtLink11B) {
			return "Link11B";
		}
		else if (this->modulation == DtRadioSystem::DtNavigationAid) {
			return "NavigationAid";
		}
		else if (this->modulation == DtRadioSystem::DtRadioSystemOther) {
			return "RadioSystemOther";
		}
		else {
			return "Sincgards";
		}
	}
	std::string print_modulation_major() {
		if (this->modulation_major == DtRadioMajorModulation::DtAmplitude) {
			return "Amplitude";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtAmplitudeAndAngle) {
			return "AmplitudeAndAngle";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtAngle) {
			return "Angle";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtCarrierPhaseShiftModulation) {
			return "CarrierPhaseShiftModulation";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtCombination) {
			return "Combination";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtPulse) {
			return "Pulse";
		}
		else if (this->modulation_major == DtRadioMajorModulation::DtRadioMajorModOther) {
			return "RadioMajorModOther";
		}
		else {
			return "Unmodulated";
		}
	}
	std::string print_antijamming() {
		if (this->antijamm == DtAntiJammingTechniqueEnum::DtAntiJammingTechniqueEnum_DSSS) {
			return "DSSS";
		}
		else if (this->antijamm == DtAntiJammingTechniqueEnum::DtAntiJammingTechniqueEnum_FHSS) {
			return "FHSS";
		}
		else if (this->antijamm == DtAntiJammingTechniqueEnum::DtAntiJammingTechniqueEnum_Tech3) {
			return "Tech3";
		}
		else {
			return "Max";
		}
	}
};

#endif