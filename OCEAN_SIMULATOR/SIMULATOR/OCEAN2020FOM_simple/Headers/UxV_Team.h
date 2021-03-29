#pragma once
#ifndef UXV_TEAM_H
#define UXV_TEAM_H
#include "UxV_Vessel.h"
#include "Target.h"


class UxV_Team{

	private:
		/***************************************************/
		/************** UXV SHIP TEAM  ATTRIBUTES **********/
		/***************************************************/

		DtExerciseConn* myExConn;
		DtEntityType usvType;

		std::vector<SHADOWING_TEAM_DATA*> team_shadowing_summary;
		std::vector<UxV_Vessel*> team;
		std::vector<Target*> targets;
		std::vector<Area_Obstacle> obstacle_status;
		std::vector<EVENT*> *team_event;
		std::vector<TARGET_STATS> targets_id;
		std::vector<FOM_EVENT *> fom_event;

		int Ship_Activated;

		DtEntityPublisher* SHIP_PUBLISHER;
		DtOCEAN2020EntityStateRepository* SHIP_PUBLISHER_SR;
		DtTopoView* SHIP_DataTopoView;
		DtVector32 SHIP_final_acceleration;
		DtVector32 SHIP_final_velocity;
		DtVector SHIP_final_possition;
		DtTaitBryan SHIP_final_orient;

		std::map<int, bool> sector_surface_status_available;
		std::map<int, bool> sector_subwater_status_available;
		std::map<int, TARGET_STATS> targets_id_history;
		std::map<int, std::vector<Dt3dPoint>> sector_surface_status;
		std::map<int, std::vector<Dt3dPoint>> sector_subwater_status;

		std::map<std::string, TEAM_JOB_STATUS*> team_status;
		std::map<std::string, Predictor_Position> position_prediction_detector;
		std::map<std::string, SHADOWING_TEAM*> teams_shawdowing;
		std::map<std::string, SHADOWING_TEAM*> teams_shawdowing_sub;

		bool bomb_activated;

		int target_num;
		int uxv_num;
		int uxv_subwater;
		int uxv_surface;
		int targets_num;
		int team_id;
		int cycleCounter;
		int ship_shadowing_team;
		int print_count;

		double refLatitude;
		double refLongitude;
		double refHeight;

		double refLatitude_init;
		double refLongitude_init;
		double refHeight_init;

		double ship_range;
		double uxv_sensor_range_sur;
		double uxv_sensor_range_sub;
		double uxv_sensor_depth_range;
		double uxv_sensor_area;
		double avoid_distance;
		double safe_distance;
		double uxv_speed_sur;
		double angle_speed_sur;
		double ACCELERATION_sur;
		double MAXIMUM_SPEED_sur;
		double DECELERATION_sur;
		double uxv_length_sur;
		double uxv_width_sur;
		double uxv_heigth_sur;
		double uxv_speed_sub;
		double angle_speed_sub;
		double ACCELERATION_sub;
		double MAXIMUM_SPEED_sub;
		double DECELERATION_sub;
		double uxv_length_sub;
		double uxv_width_sub;
		double uxv_heigth_sub;
		double vanguared_Distance_sub_depth;
		double MAX_SUBMERSION_SPEED_sub;
		double oversight_timer;
		double vanguared_distance_sur;
		double vanguared_distance_sub;
		double mass_kg_sur;
		double mass_kg_sub;

		int Naval_Base_Activate;
		double Naval_Base_Activate_degrees_tilt;

		int Jamming_Activate;
		double Jamming_time_start;

		FOM_EVENT * target_1_FOM;
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

		FOM_EVENT * target_2_FOM;
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

		std::string log_dir;
		std::string log_dir_field;
		std::string log_dir_timers;
		std::string log_dir_Kalman_Filter;
		std::string log_dir_metrics;
		std::string *target_logs;

		bool team_reset_mode_on;
		bool targets_available;
		bool tasks_available;

		char commnents;
		char commnents_basic;
		char logs;
		char logs_FOMS;
		char logs_Kalman;
		char logs_metrics;

		/***************************************************/
		/************** UXV SHIP TEAM  FUNCTIONS ***********/
		/***************************************************/
		
		Sector* create_Sectors(int, int, double, double);

		void set_up_logs_paths(char, char, char,char, std::string, std::string, std::string, std::string);
		void initialize_team_attributes(TEAM_INIT_DATA, DtExerciseConn*);
		void deploy_UxV_vessels();
		void evaluate_event(DtTime dt);
		void store_water_waves_log(Water_Waves_Kinematics*);
		void evaluate_FOM_income(Water_Waves_Kinematics*);
		void voting_shadow_team_deployment();
		void voting_shadow_team_update_surface();
		void voting_shadow_team_update_subwater();
		void created_shadow_team_surface();
		void created_shadow_team_subwater();
		void create_obstacle_enviroment();
		void update_vessels(DtTime, DtTime);
		void update_Possition_Predictor();
		void reset_team_shadowing_status();
		void check_if_vessels_is_jammed();
		void create_central_main_ship();
		void mainShipsimTick();

		void print_team_data();
		void print_team_status();
		void print_obstacle_enviroment();
		void print_voting_shadow_team();
		void print_voting_shadow_team_summarize();
		void print_sector_surface_status();
		void print_sector_availability_oversight();
		void print_target_history();

	public:

		UxV_Team(TEAM_INIT_DATA, DtExerciseConn*,char,char, char,char,char,char,std::string,std::string, std::string, std::string, std::string);
		~UxV_Team();

		void start_team_cycle(DtTime d, std::vector <EVENT*>*, DtTime simTime, Water_Waves_Kinematics*);

};

#endif
