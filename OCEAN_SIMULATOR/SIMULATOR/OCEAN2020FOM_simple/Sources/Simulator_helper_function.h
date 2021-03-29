#pragma once
#ifndef SIMULATOR_HELPER_FUNCTIONS
#define SIMULATOR_HELPER_FUNCTIONS

//[1]
/************ create_log_enviroment *************/
void Simulator::create_log_enviroment(std::string file) {
	if (this->commnents_basic == 'y') {
		print_color_message("\n----------- Set Up Log enviroment ----------------\n", 10);
	}

	//******************** Team log directory path 
	std::string simulator_log_dir = std::string(file);
	if (CreateDirectory((simulator_log_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "\n- [1] Create Simulator log directory " << simulator_log_dir << std::endl;
		}
	}
	else
	{
		if (this->commnents_basic == 'y') {
			print_color_message("\n- [1] Log directory " + simulator_log_dir + " already exists \n", 14);
		}
	}

	//******************** Team log directory path 
	std::string timestmp = "Logs_" + getTimestamp();
	std::string Logs_ = std::string(file + "\\" + timestmp);
	if (CreateDirectory((Logs_).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [2] Create log directory " << Logs_ << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory" + Logs_ + "\n", 12);
		system("pause");
		exit(-1);
	}
	//******************** Team log directory path 
	std::string simulator_Movements_log_dir = std::string(Logs_ + "/Movements");
	if (CreateDirectory((simulator_Movements_log_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [3] Create Simulator log directory " << simulator_Movements_log_dir << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory " + simulator_Movements_log_dir + " already exists \n", 12);
		system("pause");
		exit(-1);
	}
	//******************** Team log directory path 
	std::string simulator_Movements_logs_dir = std::string(simulator_Movements_log_dir + "/Logs");
	if (CreateDirectory((simulator_Movements_logs_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [4] Create Simulator log directory " << simulator_Movements_logs_dir << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory " + simulator_Movements_logs_dir + " already exists \n", 12);
		system("pause");
		exit(-1);
	}
	//******************** Team log directory path 
	std::string simulator_Fields_log_dir = std::string(Logs_ + "/Fields");
	if (CreateDirectory((simulator_Fields_log_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [5] Create Simulator log directory " << simulator_Fields_log_dir << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory" + simulator_Fields_log_dir + " already exists \n", 12);
		system("pause");
		exit(-1);
	}

	std::string simulator_Kalman_Filter_log_dir = std::string(Logs_ + "/Kalman_Filter");
	if (CreateDirectory((simulator_Kalman_Filter_log_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [6] Create Simulator log directory " << simulator_Kalman_Filter_log_dir << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory " + simulator_Kalman_Filter_log_dir + " already exists \n", 12);
		system("pause");
		exit(-1);
	}

	std::string simulator_metrics_log_dir = std::string(Logs_ + "/Metrics");
	if (CreateDirectory((simulator_metrics_log_dir).c_str(), NULL))
	{
		if (this->commnents_basic == 'y') {
			std::cout << "- [7] Create Simulator log directory " << simulator_metrics_log_dir << std::endl;
		}
	}
	else
	{
		print_color_message("Error Creating log directory " + simulator_metrics_log_dir + " already exists \n", 12);
		system("pause");
		exit(-1);
	}

	std::string simulator_Timers_log_dir = std::string(Logs_ + "/Timers.txt");
	ofstream MyFile(simulator_Timers_log_dir);
	MyFile << "SIMULATION TIMER LOGS \n\n";
	MyFile.close();
	if (this->commnents_basic == 'y') {
		std::cout << "- [8] Create Timer log File " << simulator_Timers_log_dir << std::endl;
	}
	this->log_dir = simulator_Movements_logs_dir;
	this->log_dir_field = simulator_Fields_log_dir;
	this->log_dir_timer = simulator_Timers_log_dir;
	this->log_dir_Kalman_Filter = simulator_Kalman_Filter_log_dir;
	this->log_dir_metrics = simulator_metrics_log_dir;

	std::string source_path = std::string(ExePath() + "\\Scripts\\Patroling_vessels\\");
	std::string destination_path = std::string(ExePath() + "\\" + file + "\\" + timestmp + "\\Movements\\");
	bool copy1 = CopyFile((source_path + "movement.py").c_str(), (destination_path + "movement.py").c_str(), 0);
	if (this->commnents_basic == 'y') {
		std::cout << "\n- [1] Copy py script: " << source_path + "movement.py" << std::endl;
	}
	if (!copy1) {
		print_color_message("Error while copying python scripts\n", 12);
		print_color_message(source_path + "\n", 12);
		print_color_message(destination_path + "\n", 12);
		system("pause");
		exit(-1);
	}
	bool copy2 = CopyFile((source_path + "data_Creator.py").c_str(), (destination_path + "data_Creator.py").c_str(), 0);
	if (this->commnents_basic == 'y') {
		std::cout << "- [2] Copy py script: " << source_path + "data_Creator.py" << std::endl;
	}
	if (!copy2) {
		print_color_message("Error while copying python scripts\n", 12);
		print_color_message(source_path + "\n", 12);
		print_color_message(destination_path + "\n", 12);
		system("pause");
		exit(-1);
	}
	if (this->logs_Kalman == 'y') {
		std::string source_path = std::string(ExePath() + "\\Scripts\\Possition_Prediction\\");
		std::string destination_path = std::string(ExePath() + "\\" + file + "\\" + timestmp + "\\Kalman_Filter\\");
		bool copy3 = CopyFile((source_path + "Possition_Prediction.py").c_str(), (destination_path + "Possition_Prediction.py").c_str(), 0);
		if (this->commnents_basic == 'y') {
			std::cout << "- [3] Copy py script: " << source_path + "Possition_Prediction.py" << std::endl;
		}
		if (!copy3) {
			print_color_message("Error while copying python scripts\n", 12);
			print_color_message(source_path + "\n", 12);
			print_color_message(destination_path + "\n", 12);
			system("pause");
			exit(-1);
		}
	}
	
}

//[2]
/************ read_data_from_json ***************/
void Simulator::read_data_from_json(int argc, char* argv[], std::string simulation_num, std::string file, std::string file_log) {
	double logs_js, logs_FOM_js, logs_kalman, logs_metrics;

	std::cout << "Simulator: Start .." << std::endl;
	std::cout << "Simulator: Read data from " << file << ":" << simulation_num << "\n";
	std::cout << "Simulator: Folder to store Logs " << file_log << std::endl;

	char commnents, commnents_basic;
	double commnents_js = json_reader_data(simulation_num, "Enable_comments", file);
	double commnents_js_basic = json_reader_data(simulation_num, "Enable_comments_basic", file);
	logs_js = json_reader_data(simulation_num, "Enable_Logs_movement", file);
	logs_FOM_js = json_reader_data(simulation_num, "Enable_Logs_FOMS", file);
	logs_kalman = json_reader_data(simulation_num, "Enable_Logs_KALMAN", file);
	logs_metrics = json_reader_data(simulation_num, "Enable_Logs_METRICS", file);

	if (commnents_js == 0) { commnents = 'n'; print_color_message("- No comments enabled\n", 14); }
	else { commnents = 'y'; print_color_message("- Comments enabled\n", 10); }

	if (commnents_js_basic == 0) { commnents_basic = 'n'; print_color_message("- No basic comments enabled\n", 14); }
	else { commnents_basic = 'y'; print_color_message("- Basic Comments enabled\n", 10); }

	char logs;
	if (logs_js == 0) { logs = 'n';	print_color_message("- No Logs enabled for Movements\n", 14); }
	else { logs = 'y'; print_color_message("- Logs enabled for Movements\n", 10); }

	char logs_FOMS;
	if (logs_FOM_js == 0) { logs_FOMS = 'n'; print_color_message("- No Logs enabled for FOMS\n", 14); }
	else { logs_FOMS = 'y'; print_color_message("- Logs enabled for FOMS\n", 10); }

	char logs__for_Kalman;
	if (logs_kalman == 0) { logs__for_Kalman = 'n'; print_color_message("- No Logs enabled for KALMAN\n", 14); }
	else { logs__for_Kalman = 'y'; print_color_message("- Logs enabled for KALMAN\n", 10); }

	char logs__for_metrics;
	if (logs_metrics == 0) { logs__for_metrics = 'n'; print_color_message("- No Logs enabled for METRICS\n", 14); }
	else { logs__for_metrics = 'y'; print_color_message("- Logs enabled for METRICS\n", 10); }



	this->cycles = 0;
	this->commnents = commnents;
	this->commnents_basic = commnents_basic;
	this->logs = logs;
	this->logs_FOMS = logs_FOMS;
	this->logs_Kalman = logs__for_Kalman;
	this->logs_metrics = logs__for_metrics;

	if (logs_js != 0 || logs_FOM_js != 0 || logs_kalman != 0 || logs_metrics != 0) { create_log_enviroment(file_log); }

	print_color_message("\n-- Read Data from (Input_Data.json)\n\n", 10); 
	this->uxv_team_init_data.uxv_num = json_reader_data(simulation_num, "Number_Vessel", file);
	this->uxv_team_init_data.uxv_subwater = json_reader_data(simulation_num, "Number_under_water_vessels", file);
	this->uxv_team_init_data.uxv_surface = json_reader_data(simulation_num, "Number_Surface_water_vessels", file);
	this->uxv_team_init_data.targets_num = json_reader_data(simulation_num, "Number_Targets", file);
	this->uxv_team_init_data.refLatitude = json_reader_data(simulation_num, "Ship_center_x", file);
	this->uxv_team_init_data.refLongitude = json_reader_data(simulation_num, "Ship_center_y", file);
	this->uxv_team_init_data.refHeight = json_reader_data(simulation_num, "Ship_center_z", file);
	this->uxv_team_init_data.ship_range = json_reader_data(simulation_num, "Ship_Range_meters", file);
	this->uxv_team_init_data.ship_id = json_reader_data(simulation_num, "Ship_Id", file);
	this->uxv_team_init_data.avoid_distance = json_reader_data(simulation_num, "Avoid_Distance", file);
	this->uxv_team_init_data.safe_distance = json_reader_data(simulation_num, "Safe_Distance", file);
	this->uxv_team_init_data.ship_shadowing_team = json_reader_data(simulation_num, "Ship_shadowing_team", file);
	this->uxv_team_init_data.Ship_Activated = json_reader_data(simulation_num, "Ship_Activated", file);

	this->uxv_team_init_data.oversight_timer = json_reader_data(simulation_num, "Oversight_timer", file);

	this->uxv_team_init_data.uxv_length_sur = json_reader_data(simulation_num, "Vessel_surface_X_Axis_dims_meters", file) ;
	this->uxv_team_init_data.uxv_width_sur = json_reader_data(simulation_num, "Vessel_surface_Y_Axis_dims_meters", file) ;
	this->uxv_team_init_data.uxv_heigth_sur = json_reader_data(simulation_num, "Vessel_surface_Z_Axis_dims_meters", file) ;
	this->uxv_team_init_data.uxv_length_sub = json_reader_data(simulation_num, "Vessel_subwater_X_Axis_dims_meters", file) ;
	this->uxv_team_init_data.uxv_width_sub = json_reader_data(simulation_num, "Vessel_subwater_Y_Axis_dims_meters", file) ;
	this->uxv_team_init_data.uxv_heigth_sub = json_reader_data(simulation_num, "Vessel_subwater_Z_Axis_dims_meters", file) ;

	this->uxv_team_init_data.uxv_sensor_range_sur = json_reader_data(simulation_num, "Vessel_surface_Range_radar_meters", file);
	this->uxv_team_init_data.uxv_sensor_range_sub = json_reader_data(simulation_num, "Vessel_subwater_Range_radar_meters", file) ;
	this->uxv_team_init_data.uxv_sensor_depth_range = json_reader_data(simulation_num, "Vessel_subwater_Range_radar_meters", file) ;

	this->uxv_team_init_data.angle_speed_sur = json_reader_data(simulation_num, "Vessel_surface_Speed_angular_degrees_per_sec", file);
	this->uxv_team_init_data.ACCELERATION_sur = json_reader_data(simulation_num, "Vessel_surface_Acceleration_MAX_met_per_sec_2", file) ;
	this->uxv_team_init_data.DECELERATION_sur = json_reader_data(simulation_num, "Vessel_surface_Decelaration_MAX_met_per_sec_2", file) ;
	this->uxv_team_init_data.MAXIMUM_SPEED_sur = json_reader_data(simulation_num, "Vessel_surface_Speed_MAX_met_per_sec", file);
	this->uxv_team_init_data.uxv_surface_mass = json_reader_data(simulation_num, "Vessel_surface_mass", file);

	this->uxv_team_init_data.angle_speed_sub = json_reader_data(simulation_num, "Vessel_subwater_Speed_angular_degrees_per_sec", file);
	this->uxv_team_init_data.ACCELERATION_sub = json_reader_data(simulation_num, "Vessel_subwater_Acceleration_MAX_met_per_sec_2", file);
	this->uxv_team_init_data.DECELERATION_sub = json_reader_data(simulation_num, "Vessel_subwater_Decelaration_MAX_met_per_sec_2", file);
	this->uxv_team_init_data.MAXIMUM_SPEED_sub = json_reader_data(simulation_num, "Vessel_subwater_Speed_MAX_met_per_sec", file);
	this->uxv_team_init_data.uxv_subwater_mass = json_reader_data(simulation_num, "Vessel_subwater_mass", file);

	this->uxv_team_init_data.MAX_SUBMERSION_SPEED = json_reader_data(simulation_num, "Vessel_subwater_Speed_MAX_submersion_met_per_sec", file);

	this->uxv_team_init_data.Vanguared_Distance_sub = json_reader_data(simulation_num, "Vessel_subwater_Vanguared_Distance", file) ;
	this->uxv_team_init_data.Vanguared_Distance_sur = json_reader_data(simulation_num, "Vessel_surface_Vanguared_Distance", file) ;
	this->uxv_team_init_data.Vanguared_Distance_sub_depth = json_reader_data(simulation_num, "Vessel_subwater_Vanguared_Distance_depth", file);

	this->timer_delay = json_reader_data(simulation_num, "timer_delay", file);

	this->simulation_description = { json_reader_data_description(simulation_num, file) };

	this->uxv_team_init_data.Naval_Base_Activate = json_reader_data(simulation_num, "Naval_Base_Activate", file);
	this->uxv_team_init_data.Naval_Base_Activate_degrees_tilt = json_reader_data(simulation_num, "Naval_Base_Activate_degrees_tilt", file);

	this->uxv_team_init_data.Jamming_Activate = json_reader_data(simulation_num, "Jamming_Activate", file);
	this->uxv_team_init_data.Jamming_time_start = json_reader_data(simulation_num, "Jamming_time_start", file);


	if (this->uxv_team_init_data.targets_num > 0) {
		if (this->uxv_team_init_data.targets_num <= 3) {
			this->uxv_team_init_data.target_x_1 = json_reader_data(simulation_num, "target_x_1", file);
			this->uxv_team_init_data.target_y_1 = json_reader_data(simulation_num, "target_y_1", file);
			this->uxv_team_init_data.target_z_1 = json_reader_data(simulation_num, "target_z_1", file);
			this->uxv_team_init_data.target_id_1 = json_reader_data(simulation_num, "target_id_1", file);
			this->uxv_team_init_data.target_velocity_1 = json_reader_data(simulation_num, "target_velocity_1", file) ;
			this->uxv_team_init_data.target_angle_1 = json_reader_data(simulation_num, "target_angle_1", file);
			this->uxv_team_init_data.target_start_time_1 = json_reader_data(simulation_num, "target_start_time_1", file);
			this->uxv_team_init_data.target_is_a_bomb_2 = json_reader_data(simulation_num, "target_is_a_bomb_1", file);
			this->uxv_team_init_data.target_turning_point_1_1 = json_reader_data(simulation_num, "target_turning_point_1_1", file);
			this->uxv_team_init_data.target_turning_point_2_1 = json_reader_data(simulation_num, "target_turning_point_1_2", file);
			this->uxv_team_init_data.target_turning_point_3_1 = json_reader_data(simulation_num, "target_turning_point_1_3", file);
			this->uxv_team_init_data.target_turning_point_4_1 = json_reader_data(simulation_num, "target_turning_point_1_4", file);
			this->uxv_team_init_data.target_turning_point_5_1 = json_reader_data(simulation_num, "target_turning_point_1_5", file);
			this->uxv_team_init_data.target_turning_point_6_1 = json_reader_data(simulation_num, "target_turning_point_1_6", file);
			this->uxv_team_init_data.target_turning_point_7_1 = json_reader_data(simulation_num, "target_turning_point_1_7", file);
			this->uxv_team_init_data.target_turning_point_8_1 = json_reader_data(simulation_num, "target_turning_point_1_8", file);
			this->uxv_team_init_data.target_turning_point_9_1 = json_reader_data(simulation_num, "target_turning_point_1_9", file);
			this->uxv_team_init_data.target_turning_point_10_1 = json_reader_data(simulation_num, "target_turning_point_1_10", file);
			this->uxv_team_init_data.target_turning_angle_1 = json_reader_data(simulation_num, "target_turning_angle_1", file);
		}
		if (this->uxv_team_init_data.targets_num <= 3 && this->uxv_team_init_data.targets_num >1) {
			this->uxv_team_init_data.target_x_2 = json_reader_data(simulation_num, "target_x_2", file);
			this->uxv_team_init_data.target_y_2 = json_reader_data(simulation_num, "target_y_2", file);
			this->uxv_team_init_data.target_z_2 = json_reader_data(simulation_num, "target_z_2", file);
			this->uxv_team_init_data.target_id_2 = json_reader_data(simulation_num, "target_id_2", file);
			this->uxv_team_init_data.target_velocity_2 = json_reader_data(simulation_num, "target_velocity_2", file);
			this->uxv_team_init_data.target_angle_2 = json_reader_data(simulation_num, "target_angle_2", file);
			this->uxv_team_init_data.target_start_time_2 = json_reader_data(simulation_num, "target_start_time_2", file);
			this->uxv_team_init_data.target_is_a_bomb_2 = json_reader_data(simulation_num, "target_is_a_bomb_2", file);
			this->uxv_team_init_data.target_turning_point_1_2 = json_reader_data(simulation_num, "target_turning_point_2_1", file);
			this->uxv_team_init_data.target_turning_point_2_2 = json_reader_data(simulation_num, "target_turning_point_2_2", file);
			this->uxv_team_init_data.target_turning_point_3_2 = json_reader_data(simulation_num, "target_turning_point_2_3", file);
			this->uxv_team_init_data.target_turning_point_4_2 = json_reader_data(simulation_num, "target_turning_point_2_4", file);
			this->uxv_team_init_data.target_turning_point_5_2 = json_reader_data(simulation_num, "target_turning_point_2_5", file);
			this->uxv_team_init_data.target_turning_point_6_2 = json_reader_data(simulation_num, "target_turning_point_2_6", file);
			this->uxv_team_init_data.target_turning_point_7_2 = json_reader_data(simulation_num, "target_turning_point_2_7", file);
			this->uxv_team_init_data.target_turning_point_8_2 = json_reader_data(simulation_num, "target_turning_point_2_8", file);
			this->uxv_team_init_data.target_turning_point_9_2 = json_reader_data(simulation_num, "target_turning_point_2_9", file);
			this->uxv_team_init_data.target_turning_point_10_2 = json_reader_data(simulation_num, "target_turning_point_2_10", file);
			this->uxv_team_init_data.target_turning_angle_2 = json_reader_data(simulation_num, "target_turning_angle_2", file);
		}
		if (this->uxv_team_init_data.targets_num == 3) {
			this->uxv_team_init_data.target_x_3 = json_reader_data(simulation_num, "target_x_3", file);
			this->uxv_team_init_data.target_y_3 = json_reader_data(simulation_num, "target_y_3", file);
			this->uxv_team_init_data.target_z_3 = json_reader_data(simulation_num, "target_z_3", file);
			this->uxv_team_init_data.target_id_3 = json_reader_data(simulation_num, "target_id_3", file);
			this->uxv_team_init_data.target_velocity_3 = json_reader_data(simulation_num, "target_velocity_3", file);
			this->uxv_team_init_data.target_angle_3 = json_reader_data(simulation_num, "target_angle_3", file);
			this->uxv_team_init_data.target_start_time_3 = json_reader_data(simulation_num, "target_start_time_3", file);
			this->uxv_team_init_data.target_is_a_bomb_3 = json_reader_data(simulation_num, "target_is_a_bomb_3", file);
			this->uxv_team_init_data.target_turning_point_1_3 = json_reader_data(simulation_num, "target_turning_point_3_1", file);
			this->uxv_team_init_data.target_turning_point_2_3 = json_reader_data(simulation_num, "target_turning_point_3_2", file);
			this->uxv_team_init_data.target_turning_point_3_3 = json_reader_data(simulation_num, "target_turning_point_3_3", file);
			this->uxv_team_init_data.target_turning_point_4_3 = json_reader_data(simulation_num, "target_turning_point_3_4", file);
			this->uxv_team_init_data.target_turning_point_5_3 = json_reader_data(simulation_num, "target_turning_point_3_5", file);
			this->uxv_team_init_data.target_turning_point_6_3 = json_reader_data(simulation_num, "target_turning_point_3_6", file);
			this->uxv_team_init_data.target_turning_point_7_3 = json_reader_data(simulation_num, "target_turning_point_3_7", file);
			this->uxv_team_init_data.target_turning_point_8_3 = json_reader_data(simulation_num, "target_turning_point_3_8", file);
			this->uxv_team_init_data.target_turning_point_9_3 = json_reader_data(simulation_num, "target_turning_point_3_9", file);
			this->uxv_team_init_data.target_turning_point_10_3 = json_reader_data(simulation_num, "target_turning_point_3_10", file);
			this->uxv_team_init_data.target_turning_angle_3 = json_reader_data(simulation_num, "target_turning_angle_3", file);
		}
	}

}


///////////////////////////////
// 	TESTING MODE FUNCTION    //
///////////////////////////////
void Simulator::start_simulator_T(std::string test_name, std::string simulation_num, std::string data, char* argv[])
{

	std::string data_input = "Tests/Input_Data_Target_Movement.json";
	this->read_data_from_json(1, argv, test_name, data_input, simulation_num);

	this->commnents = 'n';
	this->logs = 'y';
	this->logs_FOMS = 'y';
	this->logs_Kalman = 'y';
	this->exConn = NULL;
	if (this->commnents_basic == 'y') {
		print_color_message("\n-------------------------- TEAM CREATION ----------------------------------------- \n", 6);
	}

	this->uxv_team = new UxV_Team(this->uxv_team_init_data, this->exConn, this->commnents, this->commnents_basic, this->logs, this->logs_FOMS, this-> logs_Kalman,this->logs_metrics, this->log_dir, this->log_dir_field, this->log_dir_timer, this->log_dir_Kalman_Filter, this->log_dir_metrics);
	
	double area = 5;

	double x = (json_reader_data(test_name, "target_x", data_input));
	double y = (json_reader_data(test_name, "target_y", data_input));
	double z = (json_reader_data(test_name, "target_z", data_input));
	double vel = (json_reader_data(test_name, "target_velocity", data_input));
	double angle = (json_reader_data(test_name, "target_angle", data_input));

	int available_second_target = (json_reader_data(test_name, "available_second_target", data_input));
	double x_2 = (json_reader_data(test_name, "target_x_2", data_input));
	double y_2 = (json_reader_data(test_name, "target_y_2", data_input));
	double z_2 = (json_reader_data(test_name, "target_z_2", data_input));
	double vel_2 = (json_reader_data(test_name, "target_velocity_2", data_input));
	double angle_2 = (json_reader_data(test_name, "target_angle_2", data_input));

	int available_third_target = (json_reader_data(test_name, "available_third_target", data_input));
	double x_3 = (json_reader_data(test_name, "target_x_3", data_input));
	double y_3 = (json_reader_data(test_name, "target_y_3", data_input));
	double z_3 = (json_reader_data(test_name, "target_z_3", data_input));
	double vel_3 = (json_reader_data(test_name, "target_velocity_3", data_input));
	double angle_3 = (json_reader_data(test_name, "target_angle_3", data_input));

	int key_pressed,counter = 0;

	int iSecret = 0;
	double turn = -1;
	double random_factor = 1;
	double vessel_angle_velocity = 5;
	srand(time(NULL));

	while (counter < 1500) {
		iSecret = rand() % 10 + 1;
		if (10 - random_factor < iSecret) {
			turn = rand() % ((int)vessel_angle_velocity) + (-vessel_angle_velocity);
			angle = angle + turn;
			angle_degree_normalization(angle);
		}

		(this->team_event).push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, 1, x, y, z, angle, vel, area, "no_vessel"));
		if (available_second_target == 1) {
			(this->team_event).push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, 2, x_2, y_2, z_2, angle_2, vel_2, area, "no_vessel"));
		}
		if (available_third_target == 1) {
			(this->team_event).push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, 3, x_3, y_3, z_3, angle_3, vel_3, area, "no_vessel"));
		}
		key_pressed = keybrdTick();
		if (key_pressed == -1) { break; }
		this->uxv_team->start_team_cycle(0, &(this->team_event), 0, NULL);

		move_to_direction(x, y, vel, angle);
		move_to_direction(x_2, y_2, vel_2, angle_2);
		move_to_direction(x_3, y_3, vel_3, angle_3);

		(this->team_event).clear();
		counter++;
	}
	cout << endl;
	print_color_message("\n------------ Delete Event receiver -----------------\n", COLOR_TEXT::MAIN_TITLE_BLUE);
	this->team_event.empty();
	print_color_message("\n------------ Delete UxV Team -----------------------\n", COLOR_TEXT::MAIN_TITLE_BLUE);
	delete this->uxv_team;
	delete this->exConn;
}

#endif
