#pragma once
#ifndef UXV_TEAM_HELPER_FUNCTIONS_H
#define UXV_TEAM_HELPER_FUNCTIONS_H

//[1]
/************ set_up_logs_paths *****************/
void UxV_Team::set_up_logs_paths(char commnents, char logs, char logs_FOMS, char logs_Kalman, std::string log_dir, std::string log_dir_field, std::string log_dir_timers, std::string log_dir_Kalman_Filter) {
	this->commnents = commnents;
	this->logs = logs;
	this->logs_FOMS = logs_FOMS;
	this->logs_Kalman = logs_Kalman;
	if (this->logs == 'y') {
		this->log_dir = log_dir;
		this->log_dir_field = log_dir_field;
		this->log_dir_timers = log_dir_timers;
		this->log_dir_Kalman_Filter = log_dir_Kalman_Filter;
	}
}

//[2]
/************ initialize_team_attributes ********/
void UxV_Team::initialize_team_attributes(TEAM_INIT_DATA team_init_data, DtExerciseConn* myExConn) {

	/******************** CONNECTION **************************************/
	this->myExConn = myExConn;									// simulator connection

	/******************** TEAM ATTRIBUTES *********************************/
	this->target_logs = NULL;
	this->target_num = 0;
	this->uxv_num = team_init_data.uxv_num;						//number of vessels
	this->uxv_subwater = team_init_data.uxv_subwater;			//NUM of subwater vessels
	this->uxv_surface = team_init_data.uxv_surface;				//NUM of surface vessels
	this->targets_num = team_init_data.targets_num;

	this->Naval_Base_Activate = team_init_data.Naval_Base_Activate;
	this->Naval_Base_Activate_degrees_tilt = team_init_data.Naval_Base_Activate_degrees_tilt;
	
	this->Jamming_Activate = team_init_data.Jamming_Activate;
	this->Jamming_time_start = team_init_data.Jamming_time_start;

	this->oversight_timer = team_init_data.oversight_timer;
	if (this->uxv_surface <= 0 && this->uxv_subwater <= 0) {
		print_color_message("UxV_Team: Input Error. At least one Vessel is required\n", 12);
		system("pause");
		exit(-1);
	}
	this->team_id = 1991;										//Team ID
	this->cycleCounter = 1;										//Counter for team cycles
	this->team_reset_mode_on = false;
	this->targets_available = false;
	this->tasks_available = false;

	this->ship_range = team_init_data.ship_range;				//ship range
	this->ship_shadowing_team = team_init_data.ship_shadowing_team;

	this->refLatitude = team_init_data.refLatitude;				//initial latitude
	this->refLongitude = team_init_data.refLongitude;			//initial longitude
	this->refHeight = team_init_data.refHeight;

	for (int i = 0; i < uxv_num; i++) {
		this->fom_event.push_back(new FOM_EVENT("Team's Vessel : " + to_string(i)));
	}

	this->uxv_length_sur = team_init_data.uxv_length_sur;				//Vessel length, width, heigh sur
	this->uxv_width_sur = team_init_data.uxv_width_sur;
	this->uxv_heigth_sur = team_init_data.uxv_heigth_sur;
	this->uxv_length_sub = team_init_data.uxv_length_sub;				//Vessel length, width, heigh sub
	this->uxv_width_sub = team_init_data.uxv_width_sub;
	this->uxv_heigth_sub = team_init_data.uxv_heigth_sub;

	this->mass_kg_sub = team_init_data.uxv_subwater_mass;
	this->mass_kg_sur = team_init_data.uxv_surface_mass;


	this->safe_distance = team_init_data.safe_distance;
	this->avoid_distance = team_init_data.avoid_distance;

	if (this->uxv_length_sur > this->uxv_width_sur) {
		this->uxv_sensor_area = this->uxv_length_sur * this->uxv_length_sur;
	}
	else {
		this->uxv_sensor_area = this->uxv_width_sur * this->uxv_width_sur;
	}

	this->uxv_sensor_range_sub = team_init_data.uxv_sensor_range_sub;		//sensor range sub
	this->uxv_sensor_range_sur = team_init_data.uxv_sensor_range_sur;		//sensor range sur
	this->uxv_sensor_depth_range = team_init_data.uxv_sensor_depth_range;	//sensor depth range 

	this->vanguared_Distance_sub_depth = team_init_data.Vanguared_Distance_sub_depth;
	this->angle_speed_sub = team_init_data.angle_speed_sub;					//sensor angle speed sub
	this->MAXIMUM_SPEED_sub = team_init_data.MAXIMUM_SPEED_sub;
	this->ACCELERATION_sub = team_init_data.ACCELERATION_sub;
	this->DECELERATION_sub = team_init_data.DECELERATION_sub;
	this->MAX_SUBMERSION_SPEED_sub = team_init_data.MAX_SUBMERSION_SPEED;						//number of vessels
	this->angle_speed_sur = team_init_data.angle_speed_sur;					//sensor angle speed sur
	this->MAXIMUM_SPEED_sur = team_init_data.MAXIMUM_SPEED_sur;
	this->ACCELERATION_sur = team_init_data.ACCELERATION_sur;
	this->DECELERATION_sur = team_init_data.DECELERATION_sur;
	
	this->vanguared_distance_sur = team_init_data.Vanguared_Distance_sur;
	this->vanguared_distance_sub = team_init_data.Vanguared_Distance_sub;

	this->target_x_1 = team_init_data.target_x_1;
	this->target_y_1 = team_init_data.target_y_1;
	this->target_z_1 = team_init_data.target_z_1;
	this->target_id_1 = team_init_data.target_id_1;
	this->target_velocity_1 = team_init_data.target_velocity_1;
	this->target_angle_1 = team_init_data.target_angle_1;
	this->target_start_time_1 = team_init_data.target_start_time_1;
	this->target_is_a_bomb_1 = team_init_data.target_is_a_bomb_1;
	this->target_turning_point_1_1 = team_init_data.target_turning_point_1_1;
	this->target_turning_point_2_1 = team_init_data.target_turning_point_2_1;
	this->target_turning_point_3_1 = team_init_data.target_turning_point_3_1;
	this->target_turning_point_4_1 = team_init_data.target_turning_point_4_1;
	this->target_turning_point_5_1 = team_init_data.target_turning_point_5_1;
	this->target_turning_point_6_1 = team_init_data.target_turning_point_6_1;
	this->target_turning_point_7_1 = team_init_data.target_turning_point_7_1;
	this->target_turning_point_8_1 = team_init_data.target_turning_point_8_1;
	this->target_turning_point_9_1 = team_init_data.target_turning_point_9_1;
	this->target_turning_point_10_1 = team_init_data.target_turning_point_10_1;
	this->target_turning_angle_1 = team_init_data.target_turning_angle_1;

	this->target_x_2 = team_init_data.target_x_2;
	this->target_y_2 = team_init_data.target_y_2;
	this->target_z_2 = team_init_data.target_z_2;
	this->target_id_2 = team_init_data.target_id_2;
	this->target_velocity_2 = team_init_data.target_velocity_2;
	this->target_angle_2 = team_init_data.target_angle_2;
	this->target_start_time_2 = team_init_data.target_start_time_2;
	this->target_is_a_bomb_2 = team_init_data.target_is_a_bomb_2;
	this->target_turning_point_1_2 = team_init_data.target_turning_point_1_2;
	this->target_turning_point_2_2 = team_init_data.target_turning_point_2_2;
	this->target_turning_point_3_2 = team_init_data.target_turning_point_3_2;
	this->target_turning_point_4_2 = team_init_data.target_turning_point_4_2;
	this->target_turning_point_5_2 = team_init_data.target_turning_point_5_2;
	this->target_turning_point_6_2 = team_init_data.target_turning_point_6_2;
	this->target_turning_point_7_2 = team_init_data.target_turning_point_7_2;
	this->target_turning_point_8_2 = team_init_data.target_turning_point_8_2;
	this->target_turning_point_9_2 = team_init_data.target_turning_point_9_2;
	this->target_turning_point_10_2 = team_init_data.target_turning_point_10_2;
	this->target_turning_angle_2 = team_init_data.target_turning_angle_2;

	this->target_x_3 = team_init_data.target_x_3;
	this->target_y_3 = team_init_data.target_y_3;
	this->target_z_3 = team_init_data.target_z_3;
	this->target_id_3 = team_init_data.target_id_3;
	this->target_velocity_3 = team_init_data.target_velocity_3;
	this->target_angle_3 = team_init_data.target_angle_3;
	this->target_start_time_3 = team_init_data.target_start_time_3;
	this->target_is_a_bomb_3 = team_init_data.target_is_a_bomb_3;
	this->target_turning_point_1_3 = team_init_data.target_turning_point_1_3;
	this->target_turning_point_2_3 = team_init_data.target_turning_point_2_3;
	this->target_turning_point_3_3 = team_init_data.target_turning_point_3_3;
	this->target_turning_point_4_3 = team_init_data.target_turning_point_4_3;
	this->target_turning_point_5_3 = team_init_data.target_turning_point_5_3;
	this->target_turning_point_6_3 = team_init_data.target_turning_point_6_3;
	this->target_turning_point_7_3 = team_init_data.target_turning_point_7_3;
	this->target_turning_point_8_3 = team_init_data.target_turning_point_8_3;
	this->target_turning_point_9_3 = team_init_data.target_turning_point_9_3;
	this->target_turning_point_10_3 = team_init_data.target_turning_point_10_3;
	this->target_turning_angle_3 = team_init_data.target_turning_angle_3;
}

//[3]
/************ create_Sectors ********************/
Sector* UxV_Team::create_Sectors(int curr_sector, int divisions, double z_axis, double ship_radius) {
	double x; double y;
	double tilt;

	if (divisions <= 0) {
		divisions = 1;
	}
	if (this->Naval_Base_Activate == 1) {
		tilt = degrees_to_radians(this->Naval_Base_Activate_degrees_tilt);
		divisions = divisions * 2;
	}
	else {
		tilt = 0.0;
	}
	double theta = double(360) / double(divisions);
	Sector *current_sector = new Sector();
	if (divisions > 2) {
		current_sector->setid(curr_sector);
		current_sector->setC(new Dt3dPoint(this->refLatitude, this->refLongitude, z_axis));

		x = this->refLatitude + this->ship_range * sin(double(2 * PI * curr_sector * theta) / double(360));
		y = this->refLongitude + this->ship_range * cos(double(2 * PI * curr_sector * theta) / double(360));
		rotatePoints(x, y, this->refLatitude, this->refLongitude, tilt);
		current_sector->setB(new Dt3dPoint(x, y, z_axis));

		x = this->refLatitude + this->ship_range * sin(double(2 * PI * (curr_sector + 1) * theta) / double(360));
		y = this->refLongitude + this->ship_range * cos(double(2 * PI * (curr_sector + 1) * theta) / double(360));
		rotatePoints(x, y, this->refLatitude, this->refLongitude, tilt);

		current_sector->setA(new Dt3dPoint(x, y, z_axis));
	}
	else if (divisions == 1) {
		current_sector->setA(new Dt3dPoint(this->refLatitude, this->refLongitude, z_axis));
		current_sector->setB(new Dt3dPoint(this->refLatitude, this->refLongitude, z_axis));
		current_sector->setC(new Dt3dPoint(this->refLatitude, this->refLongitude, z_axis));
	}
	else {
		current_sector->setA(new Dt3dPoint(this->refLatitude - ship_radius, this->refLongitude, z_axis));
		current_sector->setB(new Dt3dPoint(this->refLatitude + ship_radius, this->refLongitude, z_axis));
		current_sector->setC(new Dt3dPoint(0, 0, 0));
	}
	std::vector<Dt3dPoint> poin;
	poin.push_back(*current_sector->getA());
	poin.push_back(*current_sector->getB());
	poin.push_back(*current_sector->getC());

	if (z_axis >= 0) {
	

		this->sector_surface_status.insert({ curr_sector, poin });
		this->sector_surface_status_available.insert({ curr_sector, false });
	}
	else {
		this->sector_subwater_status.insert({ curr_sector, poin });
		this->sector_subwater_status_available.insert({ curr_sector, false });
	}

	return current_sector;
}

//[4]
/********** store_water_waves_log ***************/
void UxV_Team::store_water_waves_log(Water_Waves_Kinematics* enviromental_elements) {
	if (this->logs_FOMS == 'y') {
		if (enviromental_elements->water_wave_messages_available()) {
			if (enviromental_elements->get_x_segments_2d() != 0 && enviromental_elements->get_y_segments_2d() != 0) {
				std::fstream element_field_sur;
				std::string fieldpath = this->log_dir_field + "\\" + to_string(this->cycleCounter) + "\\2d_surface_waves";
				CreateDirectory((this->log_dir_field + "\\" + to_string(this->cycleCounter)).c_str(), NULL);
				CreateDirectory((fieldpath).c_str(), NULL);

				element_field_sur.open(fieldpath + "\\2d_surface_waves.txt", std::fstream::in | std::fstream::out | std::fstream::app);
				std::string source_path = std::string(ExePath() + "\\Scripts\\Field_division_2d\\");
				std::string destination_path = std::string(fieldpath);
				CopyFile((source_path + "2d_field_division.py").c_str(), (destination_path + "\\2d_field_division.py").c_str(), 0);

				for (std::vector<ENVIROMENTAL_SURFACE_WATER_FIELD*>::iterator it = std::begin(enviromental_elements->FOM_table_surface_vess); it != std::end(enviromental_elements->FOM_table_surface_vess); ++it) {
					element_field_sur << (*it)->get_2d_square()->getPointA_x() << " " << (*it)->get_2d_square()->getPointA_y() << " "
						<< (*it)->get_2d_square()->getPointB_x() << " " << (*it)->get_2d_square()->getPointB_y() << " "
						<< (*it)->get_2d_square()->getPointC_x() << " " << (*it)->get_2d_square()->getPointC_y() << " "
						<< (*it)->get_2d_square()->getPointD_x() << " " << (*it)->get_2d_square()->getPointD_y() << " "
						<< (*it)->get_WaterSurfaceSE_wave_frequency() << " " << (*it)->get_WaterSurfaceSE_wave_direction() << " " << (*it)->get_WaterSurfaceSE_wave_height() << "\n";
				}
				element_field_sur << enviromental_elements->get_x_segments_2d() << " " << enviromental_elements->get_y_segments_2d() << "\n";
				element_field_sur.close();
			}
		}

		if (enviromental_elements->water_currect_messages_available()) {
			std::fstream element_field_sub;
			std::string fieldpath = this->log_dir_field + "\\" + to_string(this->cycleCounter) + "\\3d_current_waves";
			CreateDirectory((this->log_dir_field + "\\" + to_string(this->cycleCounter)).c_str(), NULL);
			CreateDirectory((fieldpath).c_str(), NULL);

			element_field_sub.open(fieldpath + "\\3d_current_waves.txt", std::fstream::in | std::fstream::out | std::fstream::app);
			std::string source_path = std::string(ExePath() + "\\Scripts\\Field_division_3d\\");
			std::string destination_path = std::string(fieldpath);
			CopyFile((source_path + "3d_field_division.py").c_str(), (destination_path + "\\3d_field_division.py").c_str(), 0);

			for (std::vector<ENVIROMENTAL_CURRENT_WATER_FIELD*>::iterator it = std::begin(enviromental_elements->FOM_table_subwater_vess); it != std::end(enviromental_elements->FOM_table_subwater_vess); ++it) {
				element_field_sub
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
			element_field_sub << enviromental_elements->get_x_segments_3d() << " " << enviromental_elements->get_y_segments_3d() << " " << enviromental_elements->get_z_segments_3d() << "\n";
			element_field_sub.close();
		}


	}
}

//[5]
/************ reset_team_shadowing_status *******/
void UxV_Team::reset_team_shadowing_status() {
	voting_shadow_team_update_surface();
	voting_shadow_team_update_subwater();
	for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it) {
		delete (it)->second;
	}
	for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing_sub); it != std::end(this->teams_shawdowing_sub); ++it) {
		delete (it)->second;
	}
	double xc, yc, zc;
	std::string v_name;
	for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->team_shadowing_summary); it != std::end(this->team_shadowing_summary); ++it) {
		(*it)->set_availability(true);
		(*it)->vote_leader(false);
		(*it)->set_vessel_name_leader("no_leader");
		(*it)->set_id(0);
		v_name = (*it)->get_name();
		xc = this->team_status[v_name]->current_latitude;
		yc = this->team_status[v_name]->current_longitude;
		zc = this->team_status[v_name]->current_Height;
		(*it)->update_shadow_member(xc, yc, zc, xc, yc, zc, 0, 0);
	}
	this->teams_shawdowing.clear();
	this->teams_shawdowing_sub.clear();
	this->targets_available = false;
	this->tasks_available = false;
}

//[6]
/************* update_Possition_Predictor *******/
void UxV_Team::update_Possition_Predictor() {
	double x_predict, y_predict, xp, yp, R_ = 0.1* 0.1;
	std::vector<std::string> obsolete_obstacles;
	for (std::vector<TARGET_STATS>::iterator itt = std::begin(this->targets_id); itt != std::end(this->targets_id); ++itt) {
		if ((this->position_prediction_detector).find("Target_Incoming_" + to_string((itt)->id)) == (this->position_prediction_detector).end()) {
			obsolete_obstacles.push_back("Target_Incoming_" + to_string((itt)->id));
		}
	}
	for (std::vector<std::string>::iterator itt = std::begin(obsolete_obstacles); itt != std::end(obsolete_obstacles); ++itt) {
		(this->position_prediction_detector).erase(*(itt));
	}

	for (std::vector<TARGET_STATS>::iterator itt = std::begin(this->targets_id); itt != std::end(this->targets_id); ++itt) {
		x_predict = 0.0;
		y_predict = 0.0;
		xp = (itt)->x;
		yp = (itt)->y;

		if ((this->position_prediction_detector).find("Target_Incoming_" + to_string((itt)->id)) == (this->position_prediction_detector).end()) {
			(this->position_prediction_detector).insert({ "Target_Incoming_" + to_string((itt)->id),Predictor_Position((itt)->x,(itt)->y,R_) });
			(itt)->set_xy((itt)->x, (itt)->y);
		}
		else {
			this->position_prediction_detector["Target_Incoming_" + to_string((itt)->id)].set_start_kalman_filter(&x_predict, &y_predict, (itt)->x, (itt)->y, R_);
			(itt)->set_xy(x_predict, y_predict);
		}
		if (this->logs_Kalman == 'y') {
			std::string log_dir_Kalman_Filter_vessel = std::string(this->log_dir_Kalman_Filter + "\\Target_" + to_string((itt)->id));
			std::fstream movement_output;
			movement_output.open(log_dir_Kalman_Filter_vessel + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
			movement_output << xp << " " << yp << " " << (itt)->x << " " << (itt)->y << endl;
			movement_output.close();
		}
	}
}

//[7]
/************* create_central_main_ship *********/
void UxV_Team::create_central_main_ship() {
	if (this->Ship_Activated == 1) {
		print_color_message("\n------- SHIP CREATION creation SHIP_NKUA ------------\n", COLOR_TEXT::MAIN_TITLE_GRAY);
		DtEntityType SurfaceVesselDataType(1, 3, 78, 87, 0, 0, 5);	 //1, 3, 78, 87, 0, 0, 5
		if (this->myExConn != NULL) {
			this->SHIP_PUBLISHER = new DtEntityPublisher(SurfaceVesselDataType, this->myExConn, DtDrDrmRvw, DtForceFriendly, DtEntityPublisher::guiseSameAsType());
			this->SHIP_PUBLISHER_SR = (DtOCEAN2020EntityStateRepository*)SHIP_PUBLISHER->esr();
			this->SHIP_PUBLISHER_SR->setForceId(DtForceFriendly);
			this->SHIP_PUBLISHER_SR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
			this->SHIP_PUBLISHER_SR->setGuise(SurfaceVesselDataType);
			this->SHIP_PUBLISHER_SR->setEntityType(SurfaceVesselDataType);
			this->SHIP_PUBLISHER_SR->setMarkingText("SHIP_NKUA_C");
			this->SHIP_PUBLISHER_SR->setEntityId(DtEntityIdentifier(1, 100, 1));
			this->SHIP_PUBLISHER_SR->setDimensionLength(4);
			this->SHIP_PUBLISHER_SR->setDimensionWidth(2);
			this->SHIP_PUBLISHER_SR->setDimensionHeight(2);

			this->SHIP_DataTopoView = new DtTopoView(SHIP_PUBLISHER_SR, DtDeg2Rad(this->refLatitude), DtDeg2Rad(this->refLongitude));

			this->SHIP_final_possition[0] = 0.0;
			this->SHIP_final_possition[1] = 0.0;
			this->SHIP_final_possition[2] = 0.0;

			this->SHIP_final_orient = DtTaitBryan(DtDeg2Rad(0.0), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

			this->SHIP_final_velocity[0] = 0.0;
			this->SHIP_final_velocity[1] = 0.0;
			this->SHIP_final_velocity[2] = 0.0;

			this->SHIP_final_acceleration[0] = 0.0;
			this->SHIP_final_acceleration[1] = 0.0;
			this->SHIP_final_acceleration[2] = 0.0;

			//this->SHIP_DataTopoView->setAcceleration(this->SHIP_final_acceleration);
			this->SHIP_DataTopoView->setLocation(this->SHIP_final_possition);
			this->SHIP_DataTopoView->setOrientation(this->SHIP_final_orient);
			//this->SHIP_DataTopoView->setVelocity(this->SHIP_final_velocity);

			std::cout << "------>\n";
			std::cout << "------> Reference : ";
			std::cout << this->refLatitude << "," << this->refLongitude << endl;
			std::cout << "------> DtTopoView:";
			std::cout << this->SHIP_DataTopoView->location() << endl;
			std::cout << "------> Algorithm:";
			print_color_message("     " + to_string(this->SHIP_PUBLISHER_SR->algorithm()) + "\n", COLOR_TEXT::ORANGE_COLOR);
			std::cout << "------> setMarkingText:";
			std::string mark(this->SHIP_PUBLISHER_SR->markingText());
			print_color_message("     " + mark + "\n", COLOR_TEXT::ORANGE_COLOR);
			std::cout << "------> EntityType: ";
			std::cout << this->SHIP_PUBLISHER_SR->entityType() << endl;
			std::cout << "------> Entityid  :";
			std::cout << this->SHIP_PUBLISHER_SR->entityId() << endl;
			std::cout << "------> DtForce:";
			print_color_message("      Friendly\n", COLOR_TEXT::ORANGE_COLOR);
		}
		else {
			this->SHIP_PUBLISHER = NULL;
		}
	}
}

//[8]
/************* mainShipsimTick ******************/
void UxV_Team::mainShipsimTick() {
	if (this->Ship_Activated == 1) {
		this->SHIP_final_possition[0] = 0.0;
		this->SHIP_final_possition[1] = 0.0;
		this->SHIP_final_possition[2] = 0.0;

		this->SHIP_final_orient = DtTaitBryan(DtDeg2Rad(0.0), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

		this->SHIP_final_velocity[0] = 0.0;
		this->SHIP_final_velocity[1] = 0.0;
		this->SHIP_final_velocity[2] = 0.0;

		this->SHIP_final_acceleration[0] = 0.0;
		this->SHIP_final_acceleration[1] = 0.0;
		this->SHIP_final_acceleration[2] = 0.0;


		if (this->logs == 'y') {
			std::fstream movement_output;
			movement_output << fixed << setprecision(12) << endl;
			movement_output.open(this->log_dir + "\\SHIP_NKUA.txt", std::fstream::in | std::fstream::out | std::fstream::app);
			movement_output << std::to_string(this->cycleCounter) << ": " << setprecision(12) << SHIP_final_possition[0] << ", " << setprecision(12) << SHIP_final_possition[1] << ", " << setprecision(12) << SHIP_final_possition[2] << " {0.0,0.0} ->";
			movement_output << " " << setprecision(12) << 1.0 << ", " << setprecision(12) << 1.0 << ", " << setprecision(12) << 1.0 << "\n";
			movement_output.close();
		}

		this->SHIP_DataTopoView->setLocation(this->SHIP_final_possition);
		this->SHIP_DataTopoView->setOrientation(this->SHIP_final_orient);

		this->SHIP_PUBLISHER->tick();
	}
}

//[9]
/************ print_team_data *******************/
void UxV_Team::print_team_data() {
	print_color_message("\n----------------- UxV_Team ----------------------\n", 10);
	std::cout << "--- Total Vessels        [" << this->uxv_num << "]" << std::endl;
	std::cout << "--- Surface nodes        [" << this->uxv_surface << "]" << std::endl;
	std::cout << "--- Subwater nodes       [" << this->uxv_subwater << "]" << std::endl;
	std::cout << "--- Ship Range           [" << this->ship_range << "] meters" << std::endl;
	std::cout << "--- Ship Id              [" << this->team_id << "]" << std::endl;
	std::cout << "--- Cycle tick           [" << this->cycleCounter << "]" << std::endl;

	print_color_message("\n----------------- VESSELS ------------------------\n", 14);
	for (std::map<std::string, TEAM_JOB_STATUS*>::iterator it = std::begin(team_status); it != std::end(team_status); ++it)
	{
		std::cout << "---- " << it->first << " :Job [" << getJobName(it->second->node_jobs_status) << "]" << std::endl;
		std::cout << "----- Current Possition :[" << it->second->deploy_latitude << ", " << it->second->deploy_longitude << "," << it->second->deploy_Height << "]" << std::endl;
		std::cout << "----- Sector [" << it->second->areaSector->getid() << "] " << std::endl;
		std::cout << "-----      A:[" << it->second->areaSector->getA()->x() << ", " << it->second->areaSector->getA()->y() << "] " << std::endl;
		std::cout << "-----      B:[" << it->second->areaSector->getB()->x() << "," << it->second->areaSector->getB()->y() << "] " << std::endl;
		std::cout << "-----      C:[" << it->second->areaSector->getC()->x() << "," << it->second->areaSector->getC()->y() << "] \n" << std::endl;
	}
}

//[10]
/************ print_obstacle_enviroment *********/
void UxV_Team::print_obstacle_enviroment() {
	cout << "----- Print Obstacles in Field ------ \n" << endl;
	for (std::vector<Area_Obstacle>::iterator it = std::begin(this->obstacle_status); it != std::end(this->obstacle_status); ++it)
	{
		std::cout << "Obstacle :" << (it)->get_name() << ", {" << (it)->get_x() << "," << (it)->get_y() << "," << (it)->get_z() << "} radius=" << (it)->get_radius() << "m,V="<<(it)->get_velocity()<<"m/s,A="<<(it)->get_angle() <<"deg,Job="<<(it)->get_job()<<"\n";
	}
	std::cout << "\n";
}

//[11]
/********** print voting_shadow_team *************/
void UxV_Team::print_voting_shadow_team() {
	if (!this->teams_shawdowing.empty()) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it)
		{
			(it)->second->print_shadow_teams();
		}
	}
	if (!this->teams_shawdowing_sub.empty()) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing_sub); it != std::end(this->teams_shawdowing_sub); ++it)
		{
			(it)->second->print_shadow_teams();
		}
	}
	cout << endl;
}

//[12]
/********** print voting_shadow_team ************/
void UxV_Team::print_voting_shadow_team_summarize() {
	if (!this->team_shadowing_summary.empty()) {
		std::cout << "-- Print shadowing team summary\n";
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->team_shadowing_summary); it != std::end(this->team_shadowing_summary); ++it)
		{
			std::cout << "---- " << (*it)->get_name() << ": Team (" << (*it)->get_id() << "), radius = " << (*it)->get_radius() << ",distance:" << (*it)->get_distance() << " " << " -> avail: ";
			if ((*it)->is_available()) {
				std::cout << " Yes, Leader:" << (*it)->get_vessel_name_leader();
			}
			else {
				std::cout << " No , Leader:" << (*it)->get_vessel_name_leader();
			}
			std::cout << " (Tx:" << (*it)->get_X_target() << ",Ty:" << (*it)->get_Y_target() << ") <- (" << (*it)->get_X() << "," << (*it)->get_Y() << ") {"<<(*it)->get_job()<<"}\n";
		}
	}
}

//[13]
/********** print_team_status *******************/
void UxV_Team::print_team_status() {
	std::cout << "\n-------------------------- Print status --------------------- \n";
	for (std::map<std::string, TEAM_JOB_STATUS*>::iterator it = std::begin(team_status); it != std::end(team_status); ++it)
	{
		std::cout << "------- " << it->first << " :Job [" << getJobName(it->second->node_jobs_status) << "]" << std::endl;
		std::cout << "--------- Current Possition :[" << it->second->deploy_latitude << ", " << it->second->deploy_longitude << "]" << std::endl;
		std::cout << "--------- Sector [" << it->second->areaSector->getid() << "]" << std::endl;
	}
}

//[14]
/********** print_sector_surface_status *********/
void UxV_Team::print_sector_surface_status() {
	if (!this->sector_surface_status.empty()) {
		for (std::map<int, std::vector<Dt3dPoint>>::iterator it = std::begin(this->sector_surface_status); it != std::end(this->sector_surface_status); ++it)
		{
			cout << "-->" << (it)->first << endl;
			for (std::vector<Dt3dPoint>::iterator itt = std::begin((it)->second); itt != std::end((it)->second); ++itt) {
				cout << "---->" << (itt)->x() << " " << (itt)->y() << " "<< (itt)->z() << endl;
			}
		
		}
	}
	cout << endl;
}

//[15]
/********** print_team_status *******************/
void UxV_Team::print_sector_availability_oversight() {
	std::cout << "\n-------------------------- Print Sector_availability_oversight --------------------- \n";
	for (std::map<int, bool>::iterator it = std::begin(sector_surface_status_available); it != std::end(sector_surface_status_available); ++it)
	{
		std::cout << "--> Sector [" << it->first << "] : "<<it->second << std::endl;
	}
}


void UxV_Team::print_target_history() {
	std::cout << "\n-------------------------- Print Target_history --------------------- \n";
	for (std::map<int, TARGET_STATS>::iterator it = std::begin(targets_id_history); it != std::end(targets_id_history); ++it)
	{
		std::cout << "--> Target [" << it->first << "] :[ " << it->second.x <<", "<< it->second.y <<", "<< it->second.z <<"]"<<std::endl;
	}
}

#endif
