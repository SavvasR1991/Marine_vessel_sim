#pragma once
#ifndef UXV_VESSEL_H
#define UXV_VESSEL_H
#include <matrix/geodeticCoord.h>
#include <vl/exerciseConn.h>
#include <vl/reflectedEntityList.h>
#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>
#include <vlutil/vlRtiMismatchException.h>
#include "OCEAN_Federates_Headers.h"
#include "Navigation_UxV_System.h"

class UxV_Vessel: Navigation_UxV_System {

private:
	/**************************************************/
	/***************** VESSEL ATTRIBUTES **************/
	/**************************************************/
	enum EVENT_MESSAGE event_message;

	Collision_Avoidance * collision_avoidance_detector;
	VESSEL_KINEMATICS *kinematics_status;
	VESSEL_CHARACTERISTICS * vessel_char;
	VESSEL_MOTION_VALUES *vessel_motion;
	FOM_EVENT *fom_event_evaluator;
	UxV_Vessel *ptr;
	Sector* sector;
	DtCoordTransform coordinates_transformer;

	DtOCEAN2020EntityStateRepository* VesselDataSR;
	DtEntityPublisher* VesselDataPub;
	DtTopoView* VesselDataTopoView;
	DtVector32 final_acceleration;
	DtDcm final_geocToLocalRot;
	DtVector32 final_velocity;
	DtVector final_possition;
	DtTaitBryan final_orient;
	DtExerciseConn* exConn;
	DtTime simTime;
	DtTime dt;

	Dt3dPoint* C;
	Dt3dPoint* A;
	Dt3dPoint* B;

	int id, team_id;
	int cycleCounter;
	int velocity_status;
	int team_id_shadow;
	int sector_id_oversight;
	int jam_timer;
	int jam_time_detonation;

	std::string log_dir;
	std::string log_dir_timer;
	std::string log_dir_Kalman_Filter;

	std::string enviromental_attr;
	std::string leader_vangared_name;

	std::vector<string> target_name_history;

	double refLatitude_init;
	double refLongitude_init;

	char status;
	char comments;
	char logs;
	char job;
	char job_previous;
	char mode;
	char logs_Kalman;
	char logs_timer;

	std::vector<Area_Obstacle> obstacles;
	std::vector<Area_Obstacle> obstacles_Kalman_Predicted;
	std::vector<Area_Obstacle>  *obstacle_status;
	std::vector<SHADOWING_TEAM_DATA*>  *my_team_shawdowing_voted;

	std::map<int, bool> *sector_surface_status_available;
	std::map<int, bool> *sector_subwater_status_available;
	std::map<int, std::vector<Dt3dPoint>> *sector_surface_status;
	std::map<int, std::vector<Dt3dPoint>> *sector_subwater_status;
	std::map<std::string, SHADOWING_TEAM*> *teams_shadowing_status;
	std::map<std::string, Predictor_Position> position_prediction_detector;
	std::map<std::string, double> target_distances;
	std::map<std::string, double> target_detect;
	std::map<std::string, int> target_distances_timer;

	std::list<Point*> patroling_points;
	std::list<Point*> oversight_points;
	list<Point*>::iterator current_patroling_point;
	list<Point*>::iterator current_oversight_point;

	bool shadow_team_leader;
	bool detected_target;
	bool reset_mode_on;
	bool lock_mode_on;
	bool oversight_mode_on;
	bool out_of_area;
	bool emegercy_avoidance_on;
	bool team_is_locked;
	bool recovery_activation;
	bool reassignment_activation;

	double x_leader_overview;
	double y_leader_overview;
	double z_leader_overview;
	double safe_distance;
	double avoid_distance;
	double ship_range;
	double maximum_speed_submersion;
	double vanguard_distance;
	double oversight_timer;
	double oversight_timer_temp;
	double target_X;
	double target_Y;
	double target_Z;

	double mass_kg;

	double vanguared_Distance_sub_depth;
	/********** METRICS DATA *****************/
	double total_ticks;
	double total_time;

	double vangared_ticks;
	double vangured_time;

	double locked_ticks;
	double locked_time;

	double locked_ticks_2;
	double locked_time_2;

	double oversigh_ticks;
	double oversigh_time;

	double survilance_ticks;
	double survilance_time;

	double jam_ticks;
	double jam_time;

	double reassignment_jam_ticks;
	double reassignment_jam_time;

	double reassignment_ticks;
	double reassignment_time;

	double reset_ticks;
	double reset_time;

	double full_patroling_ticks;
	double full_patroling_time;

	double average_distanc_fr_target;
	double average_distanc_fr_target2;

	double average_distanc_fr_center;

	int patroling_ponts_total;
	int patroling_ponts_total_length;
	bool full_patroling_complete;

	/********** NAVIGATION JOBS **************/
	void move();
	void accelerate();
	void decelerate();
	void speed_balancing_equalizer();
	void angle_balancing_equalizer();
	bool radar_detection(double x0, double y0, double x1, double y1, double radius);
	bool depth_detection();
	char* display_compass_direction(double x0, double y0, double x1, double y);
	void update_mode();

	/********** VESSEL FUNCTIONS ************/
	bool evaluateEvent(std::vector <EVENT*>*, FOM_EVENT*);
	bool execute(DtTime dt);
	bool publish_possition();
	bool waves;
	void set_FOM_disruptions();
	void radar_detection_scanning();
	void resetVessel_Values();
	void evaluate_reset();
	void evaluate_target_income();
	void evaluate_no_message();
	void set_Vessel_data(VESSEL_INIT_DATA);
	void create_Patroling_Points(VESSEL_INIT_DATA, double&, double&, double&, double&);
	void set_Vessel_kinematics_init(VESSEL_INIT_DATA, double, double, double, double);
	void create_Vessel_Subwater(std::map<std::string, SHADOWING_TEAM*>*);
	void create_Vessel_Surface(std::map<std::string, SHADOWING_TEAM*>*);
	void create_Vessel_Publisher();
	void create_Vessel_Publisher_sub();
	void set_current_job();

	void move_to_possition(DtTime dt);
	void save_print_vessel_possition();
	void check_if_out_of_patroling_area();
	void store_metrics();

	void print_shadow_team();
	void print_Obstacle_array();
	void print_Obstacle_array_total();
	void print_Predictor_total();
	void print_xy_oversight();

public:
	/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
	UxV_Vessel(VESSEL_INIT_DATA, DtExerciseConn*,char,char,char,std::vector<Area_Obstacle>*, std::map<std::string, SHADOWING_TEAM*>*, std::map<std::string, SHADOWING_TEAM*>*, std::map<int, bool>*, std::map<int, bool>*, std::map<int, std::vector<Dt3dPoint>>*, std::map<int, std::vector<Dt3dPoint>>*, int);
	~UxV_Vessel();

	/****************** GETTERS /SETTERS ******************************/
	void setSector(Sector *);
	void set_detected_target(double);
	void set_xy_leader_overview(double, double);
	void set_z_leader_overview(double);
	void set_xy_oversight(std::vector<double>, std::vector<double>);
	void set_oversight_mode_on(bool);
	void set_sector_id_oversight(int);
	void set_recovery_activation(bool);
	void set_jam_time_detonation(int);
	void set_job(JOB);

	VESSEL_KINEMATICS* get_current_kinematics();
	double get_x();
	double get_y();
	double get_z();
	double get_mass_kg();
	double get_deploy_x();
	double get_deploy_y();
	double get_deploy_z();
	double get_reference_angle_horizontal();
	double get_reference_angle_vertical();
	double get_linear_velocity();
	double get_angular_velocity();
	double get_mass();
	double get_length();
	double get_width();
	double get_craft();
	double get_radius();
	double get_scanning_radius();
	bool get_out_of_area();
	bool get_reset_mode_on();
	bool get_team_is_locked();
	bool get_oversight_mode_on();
	bool get_recovery_activation();
	std::string getName();
	std::string getType();
	char getJob();
	char getStatus();

	/****************** TRIGGER VESSEL FOR EVENT **********************/
	bool VesselsimTick(DtTime dt, std::map<std::string, TEAM_JOB_STATUS*>, std::vector <EVENT*>*, FOM_EVENT*, DtTime, int);
};

#endif