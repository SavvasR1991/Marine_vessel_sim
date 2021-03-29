#pragma once
#ifndef UXV_VESSEL_HELPER_FUNCTIONS_H
#define UXV_VESSEL_HELPER_FUNCTIONS_H

//[1]
/***************** print_shadow_team **************/
void UxV_Vessel::print_shadow_team() {
	if (this->my_team_shawdowing_voted != NULL) {
		std::cout << "---- Vessel :" << vessel_char->get_name() << " print shadowing team" << std::endl;
		std::cout << "---- Id: " << (*this->my_team_shawdowing_voted)[0]->get_id()
			<< ", Leader: " << (*this->my_team_shawdowing_voted)[0]->get_vessel_name_leader()
			<< " [" << (*this->my_team_shawdowing_voted)[0]->get_X_target()
			<< " ," << (*this->my_team_shawdowing_voted)[0]->get_Y_target()
			<< " ," << (*this->my_team_shawdowing_voted)[0]->get_Z_target() << "]" << std::endl;
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(*(this->my_team_shawdowing_voted)); it != std::end(*(this->my_team_shawdowing_voted)); ++it)
		{
			std::cout << "------ " << (*it)->get_name() << " [" << (*it)->get_X() << "," << (*it)->get_Y() << "," << (*it)->get_Z() << "]" << std::endl;
		}
	}
}

//[2]
/***************** print_Obstacle_array ***********/
void UxV_Vessel::print_Obstacle_array() {
	for (std::vector<Area_Obstacle>::iterator it = std::begin((this->obstacles)); it != std::end((this->obstacles)); ++it) {
		std::cout << "Obstacle :" << (it)->get_distance() << "m, {" << (it)->get_x() << "," << (it)->get_y() << "," << (it)->get_z() << "} radius=" << (it)->get_radius() << "m Name" << (it)->get_name() << "\n";
	}
	std::cout << "\n";
}

//[3]
/***************** print_Obstacle_array_total *****/
void UxV_Vessel::print_Obstacle_array_total() {
	for (std::vector<Area_Obstacle>::iterator it = std::begin(*this->obstacle_status); it != std::end(*this->obstacle_status); ++it)
	{
		std::cout << "Obstacle :" << (it)->get_name() << ", {" << (it)->get_x() << "," << (it)->get_y() << "," << (it)->get_z() << "} radius=" << (it)->get_radius() << "m\n";
	}
	std::cout << "\n";
}

//[4]
/***************** print_Predictor_total **********/
void UxV_Vessel::print_Predictor_total() {
	cout << "---" << this->getName() << endl;
	for (std::map<std::string, Predictor_Position>::iterator it = std::begin(this->position_prediction_detector); it != std::end(this->position_prediction_detector); ++it)
	{
		std::cout << "Obstacle :" << (it)->first << "\n";
	}
	std::cout << "\n";
}

//[5]
/***************** print_xy_oversight *************/
void UxV_Vessel::print_xy_oversight() {
	cout << "-- " << this->getName() << endl;
	for (std::list<Point*>::iterator it = std::begin(this->oversight_points); it != std::end(this->oversight_points); ++it) {

		cout << (*it)->x() << " " << (*it)->y() <<" "<< (*it)->z() << endl;
	}
	cout << endl;
}

//[6]
/************* resetVessel_Values *****************/
void UxV_Vessel::resetVessel_Values() {
	this->detected_target = false;
	this->shadow_team_leader = false;
	this->team_is_locked = false;
	this->lock_mode_on = false;
	this->my_team_shawdowing_voted = NULL;
	this->team_id_shadow = 0;
	this->oversight_mode_on = false;
	this->leader_vangared_name = "no_leader";
	this->oversight_timer_temp = 0;
	this->reset_mode_on = true;
	this->mode = MODE::LOITER_SURVEILANCE;
	this->job = JOB::RESET;
	this->job_previous = JOB::RESET;
	this->event_message = EVENT_MESSAGE::RESET_VESSELS;
	this->x_leader_overview = 0;
	this->y_leader_overview = 0;
	this->sector_id_oversight = -1;
	this->oversight_points.clear();
}

//[7]
/************* resetVessel_Values *****************/
void UxV_Vessel::create_Patroling_Points(VESSEL_INIT_DATA vessel_data,double &x_dep, double &y_dep, double &x_reset, double &y_reset){
	std::fstream movement_output;
	std::list<Point*>::iterator it;
	int tmp = 1, count = 0;
	if (this->vessel_char->get_type() == "SUB_ROV") {			//**** SUBWATER TYPE ****//
		this->maximum_speed_submersion = vessel_data.maximum_speed_submersion;
		if (!this->sector->check_if_is_one_point()) {
			if (this->C->x() == 0 && this->C->y() == 0 && this->C->z() == 0) {
				create_patroling_reference_points_in_semi_cycles(this->patroling_points, vessel_char->get_area_radius(), this->ship_range, vessel_data.refLatitude, vessel_data.refLongitude, vessel_data.refHeight, vessel_data.name);
				this->current_patroling_point = this->patroling_points.begin();
				concatenate_reverse_list(this->patroling_points);
			}
			else {
				create_patroling_reference_points(this->patroling_points, vessel_char->get_area_radius(), C->x(), C->y(), A->x(), A->y(), B->x(), B->y(), (vessel_data.refHeight));
				this->current_patroling_point = this->patroling_points.begin();
				concatenate_reverse_list(this->patroling_points);
			}
		}
		else {
			create_patroling_reference_points_in_cycles(this->patroling_points, vessel_char->get_area_radius(), this->ship_range, vessel_data.refLatitude, vessel_data.refLongitude, vessel_data.refHeight);
			this->current_patroling_point = this->patroling_points.begin();
			concatenate_reverse_list(this->patroling_points);
		}
	}
	else {												//**** SURFACE TYPE ****//

		create_patroling_reference_points(this->patroling_points, vessel_char->get_area_radius(), C->x(), C->y(), A->x(), A->y(), B->x(), B->y(), 0);
		this->current_patroling_point = this->patroling_points.begin();
		concatenate_reverse_list(this->patroling_points);
	}

	if (this->logs == 'y') {
		movement_output.open(log_dir + "\\" + vessel_char->get_name() + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
		movement_output << "Patroling Sections:\n";
	}

	for (it = patroling_points.begin(); it != patroling_points.end(); ++it) {
		if (this->logs == 'y') {
			movement_output << "[" << setprecision(12) <<  (*it)->x() << ", " << setprecision(12) << (*it)->y() << "," << setprecision(12) << (*it)->z() << "] -> ";
			if (tmp % 2 == 0) {
				movement_output << "\n";
			}
		}
		if (count == 1) {
			x_dep = (*it)->x();
			y_dep = (*it)->y();
		}
		if (count == (int)(patroling_points.size() / 2)) {
			x_reset = (*it)->x();
			y_reset = (*it)->y();
		}
		count++;
		tmp++;
	}
	if (this->logs == 'y') {
		movement_output << " End \n\n";
		movement_output.close();
	}
}

//[8]
/************* resetVessel_Values *****************/
void UxV_Vessel::set_Vessel_data(VESSEL_INIT_DATA vessel_data) {
	this->vessel_char->set_current_dimensions(vessel_data.height, vessel_data.length, vessel_data.width, vessel_data.mass, vessel_data.sensor_range, vessel_data.sensor_depth_range, vessel_data.type, vessel_data.name);
	this->mass_kg = vessel_data.mass;
	this->vessel_motion->set_current_values(vessel_data.acceleration, vessel_data.deceleration, vessel_data.angle_speed, vessel_data.maximum_speed, 0.0, vessel_data.acceleration, vessel_data.acceleration_decent);
	this->team_id = vessel_data.team_id;				//Team id
	this->id = vessel_data.id_type;						//Vessel id
	this->log_dir = vessel_data.log_dir;				//Log directory
	this->log_dir_timer = vessel_data.log_dir_timer;	//Log directory
	this->status = 'A';									//Vessel status (active, damaged etc)
	this->event_message = NO_MESSAGE;					//Event message no message
	this->job = JOB::PATROLING;							//Current movement, start patroling
	this->job_previous = JOB::PATROLING;
	this->mode = MODE::LOITER_SURVEILANCE;
	this->reset_mode_on = false;						//Is reset mode active
	this->oversight_mode_on = false;						//Is reset mode active
	this->detected_target = false;						//Is any target detected in range?
	this->lock_mode_on = false;							//Is lock mode activated
	this->team_is_locked = false;
	this->shadow_team_leader = false;
	this->out_of_area = false;
	this->recovery_activation = false;
	this->emegercy_avoidance_on = false;
	this->leader_vangared_name = "no_leader";
	this->team_id_shadow = 0;
	this->safe_distance = vessel_data.safe_distance;
	this->avoid_distance = vessel_data.avoid_distance;
	this->ship_range = vessel_data.ship_range;
	this->oversight_timer = vessel_data.oversight_timer;
	this->oversight_timer_temp = 0;
	this->x_leader_overview = 0;
	this->y_leader_overview = 0;
	this->sector_id_oversight = -1;
	this->vanguard_distance = vessel_data.vanguard_distance;
	this->vanguared_Distance_sub_depth = vessel_data.vanguared_Distance_sub_depth;

	std::cout << "---- Sector set up" << std::endl;
	this->sector = vessel_data.sector;

	this->A = sector->getA();
	this->B = sector->getB();
	this->C = sector->getC();

}

//[9]
/************* set_Vessel_kinematics_init *********/
void UxV_Vessel::set_Vessel_kinematics_init(VESSEL_INIT_DATA vessel_data, double x_dep, double y_dep, double x_reset, double y_reset) {
	double init_dest_x = (*this->current_patroling_point)->x();
	double init_dest_y = (*this->current_patroling_point)->y();
	double init_dest_z = (*this->current_patroling_point)->z();

	this->kinematics_status->set_reference_xyz(vessel_data.refLatitude, vessel_data.refLongitude, 0);
	this->kinematics_status->set_destination_xyz(init_dest_x, init_dest_y, init_dest_z);
	this->kinematics_status->set_safe_xyz(init_dest_x, init_dest_y, init_dest_z);
	this->kinematics_status->set_deploy_xyz(x_dep, y_dep, 0);
	this->kinematics_status->set_reset_xyz(x_reset, y_reset, 0);

	double angle_2d_point_horizontal = angle_between_2d_points(kinematics_status->get_deploy_x(), kinematics_status->get_deploy_y(), this->kinematics_status->get_destination_x(), this->kinematics_status->get_destination_y());
	this->kinematics_status->set_destination_theta_horizontal(angle_2d_point_horizontal);
	this->kinematics_status->set_current_theta_horizontal(this->kinematics_status->get_destination_theta_horizontal());
	this->kinematics_status->set_destination_theta_vertical(0);
	this->kinematics_status->set_current_theta_vertical(0);
	this->refLatitude_init = vessel_data.deploy_latitude_INIT;
	this->refLongitude_init = vessel_data.deploy_longitude_INIT;

	if (vessel_char->get_type() == "SUB_ROV") {			//**** SUBWATER TYPE ****//
		kinematics_status->set_deploy_z(vessel_data.refHeight);
		kinematics_status->set_reference_z(vessel_data.refHeight);			//Reference Height
		this->kinematics_status->set_destination_z(this->kinematics_status->get_deploy_z());
		this->enviromental_attr = "WATER_CURRENT";
	}
	else {
		this->kinematics_status->set_destination_z(0);
		this->enviromental_attr = "WATER_SURFACE";
	}
	this->kinematics_status->set_current_xyz(this->kinematics_status->get_deploy_x(), this->kinematics_status->get_deploy_y(), this->kinematics_status->get_deploy_z());
}

//[10]
/************* create_Vessel_Subwater *************/
void UxV_Vessel::create_Vessel_Subwater(std::map<std::string, SHADOWING_TEAM*>* teams_shadowing_status_sub) {
	this->teams_shadowing_status = teams_shadowing_status_sub;
	DtEntityType SubmersibleVesselDataType(1, 4, 82, 8, 1, 0, 1); //1:4:82:8:1:0:1
	if (this->exConn != NULL) {
		this->VesselDataPub = new DtEntityPublisher(SubmersibleVesselDataType, this->exConn, DtDrDrmRvw, DtForceFriendly, DtEntityPublisher::guiseSameAsType());
		create_Vessel_Publisher_sub();
	}
	else {
		this->VesselDataPub = NULL;
	}
}

//[11]
/************* create_Vessel_Surface **************/
void UxV_Vessel::create_Vessel_Surface(std::map<std::string, SHADOWING_TEAM*>* teams_shadowing_status) {
	this->teams_shadowing_status = teams_shadowing_status;
	DtEntityType SurfaceVesselDataType(1, 3, 82, 19, 0, 0, 82);	 //1:3:82:19:0:0:82
	if (this->exConn != NULL) {
		this->VesselDataPub = new DtEntityPublisher(SurfaceVesselDataType, this->exConn, DtDrDrmRvw, DtForceFriendly, DtEntityPublisher::guiseSameAsType());
		create_Vessel_Publisher();
	}
	else {
		this->VesselDataPub = NULL;
	}
}

//[12]
/************* create_Vessel_Publisher ************/
void UxV_Vessel::create_Vessel_Publisher() {
	int type_id = 1000;	
	if (this->exConn != NULL) {
		DtEntityType SurfaceVesselDataType(1, 3, 82, 19, 0, 0, 82);	 //1:3:82:19:0:0:82
		this->VesselDataSR = (DtOCEAN2020EntityStateRepository*)VesselDataPub->esr();
		this->VesselDataSR->setForceId(DtForceFriendly);
		this->VesselDataSR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
		this->VesselDataSR->setGuise(SurfaceVesselDataType);
		this->VesselDataSR->setEntityType(SurfaceVesselDataType);
		this->VesselDataSR->setMarkingText((this->getName()).c_str());
		this->VesselDataSR->setEntityId(DtEntityIdentifier(this->team_id, type_id, this->id));
		this->VesselDataSR->setDimensionLength(this->get_length());
		this->VesselDataSR->setDimensionWidth(this->get_width());
		this->VesselDataSR->setDimensionHeight(this->get_craft());

		this->VesselDataTopoView = new DtTopoView(VesselDataSR, DtDeg2Rad(this->refLatitude_init), DtDeg2Rad(this->refLongitude_init));
		
		this->final_possition[0] = (this->kinematics_status->get_deploy_x());
		this->final_possition[1] = (this->kinematics_status->get_deploy_y());
		this->final_possition[2] = 0.0; // DtDeg2Rad(this->kinematics_status->get_current_z());

		this->final_orient = DtTaitBryan(DtDeg2Rad(this->kinematics_status->get_current_theta_horizontal()), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

		this->final_velocity[0] = 0.0;
		this->final_velocity[1] = 0.0;
		this->final_velocity[2] = 0.0;

		this->final_acceleration[0] = 0.0;
		this->final_acceleration[1] = 0.0;
		this->final_acceleration[2] = 0.0;

		this->VesselDataTopoView->setAcceleration(this->final_acceleration);
		this->VesselDataTopoView->setLocation(this->final_possition);
		this->VesselDataTopoView->setOrientation(this->final_orient);
		this->VesselDataTopoView->setVelocity(this->final_velocity);

		std::cout << "------>\n";
		std::cout << "------> Reference : ";
		std::cout << refLatitude_init <<","<< refLongitude_init << " rad: "<< DtDeg2Rad(this->kinematics_status->get_current_theta_horizontal())<< endl;
		std::cout << "------> DtTopoView:";
		std::cout << this->VesselDataTopoView->location() << endl;
		std::cout << "------> Algorithm:";
		print_color_message("     " + to_string(this->VesselDataSR->algorithm()) + "\n", COLOR_TEXT::ORANGE_COLOR);
		std::cout << "------> setMarkingText:";
		std::string mark(this->VesselDataSR->markingText());
		print_color_message("     " + mark + "\n", COLOR_TEXT::ORANGE_COLOR);
		std::cout << "------> EntityType: ";
		std::cout << this->VesselDataSR->entityType()<< endl;
		std::cout << "------> Entityid  :";
		std::cout << this->VesselDataSR->entityId() << endl;
		std::cout << "------> DtForce:";
		print_color_message("      Friendly\n", COLOR_TEXT::ORANGE_COLOR);
	}
}

void UxV_Vessel::create_Vessel_Publisher_sub() {
	int type_id = 1005;
	if (this->exConn != NULL) {
		DtEntityType SurfaceVesselDataType(1, 4, 82, 8, 1, 0, 1);	 //1, 4, 82, 8, 1, 0, 1
		this->VesselDataSR = (DtOCEAN2020EntityStateRepository*)VesselDataPub->esr();
		this->VesselDataSR->setForceId(DtForceFriendly);
		this->VesselDataSR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
		this->VesselDataSR->setGuise(SurfaceVesselDataType);
		this->VesselDataSR->setEntityType(SurfaceVesselDataType);
		this->VesselDataSR->setMarkingText((this->getName()).c_str());
		this->VesselDataSR->setEntityId(DtEntityIdentifier(this->team_id, type_id, this->id));
		this->VesselDataSR->setDimensionLength(this->get_length());
		this->VesselDataSR->setDimensionWidth(this->get_width());
		this->VesselDataSR->setDimensionHeight(this->get_craft());

		this->VesselDataTopoView = new DtTopoView(VesselDataSR, DtDeg2Rad(this->refLatitude_init), DtDeg2Rad(this->refLongitude_init));

		this->final_possition[0] = (this->kinematics_status->get_deploy_x());
		this->final_possition[1] = (this->kinematics_status->get_deploy_y());
		this->final_possition[2] = (this->kinematics_status->get_current_z());

		this->final_orient = DtTaitBryan(DtDeg2Rad(this->kinematics_status->get_current_theta_horizontal()), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

		this->final_velocity[0] = 0.0;
		this->final_velocity[1] = 0.0;
		this->final_velocity[2] = 0.0;

		this->final_acceleration[0] = 0.0;
		this->final_acceleration[1] = 0.0;
		this->final_acceleration[2] = 0.0;

		this->VesselDataTopoView->setAcceleration(this->final_acceleration);
		this->VesselDataTopoView->setLocation(this->final_possition);
		this->VesselDataTopoView->setOrientation(this->final_orient);
		this->VesselDataTopoView->setVelocity(this->final_velocity);

		std::cout << "------>\n";
		std::cout << "------> Reference : ";
		std::cout << refLatitude_init << "," << refLongitude_init << " rad: " << DtDeg2Rad(this->kinematics_status->get_current_theta_horizontal()) << endl;
		std::cout << "------> DtTopoView:";
		std::cout << this->VesselDataTopoView->location() << endl;
		std::cout << "------> Algorithm:";
		print_color_message("     " + to_string(this->VesselDataSR->algorithm()) + "\n", COLOR_TEXT::ORANGE_COLOR);
		std::cout << "------> setMarkingText:";
		std::string mark(this->VesselDataSR->markingText());
		print_color_message("     " + mark + "\n", COLOR_TEXT::ORANGE_COLOR);
		std::cout << "------> EntityType: ";
		std::cout << this->VesselDataSR->entityType() << endl;
		std::cout << "------> Entityid  :";
		std::cout << this->VesselDataSR->entityId() << endl;
		std::cout << "------> DtForce:";
		print_color_message("      Friendly\n", COLOR_TEXT::ORANGE_COLOR);
	}
}

//[13]
/************* save_print_vessel_possition ********/
void UxV_Vessel::save_print_vessel_possition() {
	double dest_x = this->kinematics_status->get_destination_x();
	double dest_y = this->kinematics_status->get_destination_y();
	double dest_z = this->kinematics_status->get_destination_z();
	double theta_hor = this->kinematics_status->get_current_theta_horizontal();
	double theta_ver = this->kinematics_status->get_destination_theta_horizontal();
	std::string jo(1, this->job);
	if (this->logs == 'y') {
		std::fstream movement_output;
		movement_output << fixed << setprecision(12) << endl;
		movement_output.open(log_dir + "\\" + vessel_char->get_name() + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
		movement_output << std::to_string(this->cycleCounter) << ": " << setprecision(12) << this->kinematics_status->get_current_x() << ", " << setprecision(12) << this->kinematics_status->get_current_y() << ", " << setprecision(12) << final_possition[2] << " {" << theta_hor << ", " << theta_ver << "} ->";
		movement_output << " " << setprecision(12) << dest_x << ", " << setprecision(12) << dest_y << ", " << setprecision(12) << dest_z << "\n";
		movement_output.close();
	}
}

//[14]
/***************** movements kinematics ***********/
void UxV_Vessel::move() {
	Navigation::move(this->kinematics_status, this->vessel_motion, this->vessel_char,this->dt);
}
void UxV_Vessel::accelerate() {}
void UxV_Vessel::decelerate() {}
void UxV_Vessel::speed_balancing_equalizer() {
	Navigation::speed_balancing_equalizer(this->kinematics_status, this->vessel_motion, this->vessel_char, this->dt);

}
void UxV_Vessel::angle_balancing_equalizer() {
	Navigation::angle_balancing_equalizer(this->kinematics_status, this->vessel_motion, this->vessel_char, this->dt, this->waves);
}
bool UxV_Vessel::radar_detection(double x0, double y0, double x1, double y1, double radius) {
	return Navigation::radar_detection(x0, y0, x1, y1, radius);
}
bool UxV_Vessel::depth_detection() {
	return false;
}
char* UxV_Vessel::display_compass_direction(double x0, double y0, double x1, double y1) {
	return Navigation::display_compass_direction(x0, y0, x1, y1);
}
void UxV_Vessel::update_mode() {
	if (this->getJob() == JOB::PATROLING || this->getJob() == JOB::RESET) {
		this->mode = MODE::LOITER_SURVEILANCE;
	}
	else {
		this->mode = MODE::TRACKING_SHADOWING;
	}
}

//[15]
/***************** GETTERS/SETTERS *****************/
double UxV_Vessel::get_x() { return this->kinematics_status->get_current_x(); }												// get x
double UxV_Vessel::get_y() { return this->kinematics_status->get_current_y(); }												// get y
double UxV_Vessel::get_z() { return this->kinematics_status->get_current_z(); }												// get z
double UxV_Vessel::get_deploy_x() { return this->kinematics_status->get_deploy_x(); };										// get xdep
double UxV_Vessel::get_deploy_y() { return this->kinematics_status->get_deploy_y(); };										// get ydep		
double UxV_Vessel::get_deploy_z() { return this->kinematics_status->get_deploy_z(); };										// get zdep
double UxV_Vessel::get_reference_angle_horizontal() { return this->kinematics_status->get_reference_theta_horizontal(); }	// get reference theta
double UxV_Vessel::get_reference_angle_vertical() { return this->kinematics_status->get_reference_theta_vertical(); }		// get reference theta
double UxV_Vessel::get_linear_velocity() { return this->vessel_motion->get_speed(); }										// get linear Vel
double UxV_Vessel::get_angular_velocity() { return this->vessel_motion->get_Max_angle_speed(); }							// get Angular Vel
double UxV_Vessel::get_mass() { return vessel_char->get_mass(); }															// get mass
double UxV_Vessel::get_mass_kg() { return this->mass_kg; }															// get mass

double UxV_Vessel::get_length() { return vessel_char->get_length(); }														// get length
double UxV_Vessel::get_width() { return vessel_char->get_width(); }															// get width
double UxV_Vessel::get_craft() { return vessel_char->get_height(); }														// get height
double UxV_Vessel::get_radius() { return vessel_char->get_area_radius(); }													// get radius
double UxV_Vessel::get_scanning_radius() { return vessel_char->get_scanning_radius(); }										// get radius
bool UxV_Vessel::get_reset_mode_on() { return this->reset_mode_on; }
bool UxV_Vessel::get_out_of_area() { return this->out_of_area; }
bool UxV_Vessel::get_team_is_locked() { return this->team_is_locked; }
bool UxV_Vessel::get_oversight_mode_on() { return this->oversight_mode_on; }
bool UxV_Vessel::get_recovery_activation() { return this->recovery_activation; }
char UxV_Vessel::getJob() { return this->job; }																				// get job
char UxV_Vessel::getStatus() { return this->status; }																		// get status
std::string UxV_Vessel::getName() { return vessel_char->get_name(); }														// get name
std::string UxV_Vessel::getType() { return vessel_char->get_type(); }														// get name
VESSEL_KINEMATICS* UxV_Vessel::get_current_kinematics() { return this->kinematics_status; }									// get kinematics

void UxV_Vessel::setSector(Sector * sector) { this->sector = sector; }														// set sector
void UxV_Vessel::set_oversight_mode_on(bool set) { this->oversight_mode_on = set; }
void UxV_Vessel::set_detected_target(double detected_target) { this->detected_target = detected_target; }
void UxV_Vessel::set_xy_leader_overview(double x, double y) {
	this->x_leader_overview = x;
	this->y_leader_overview = y;
}
void UxV_Vessel::set_z_leader_overview(double x) {
	this->z_leader_overview = x;
}
void UxV_Vessel::set_xy_oversight(std::vector<double> xx, std::vector<double> yy) {
	Point *P;
	int counter = 0;
	for (std::vector<double>::iterator it_summ = std::begin(xx); it_summ != std::end(xx); ++it_summ) {
		P = new Point((*it_summ), (yy).at(counter), 0);
		oversight_points.push_back(P);
		counter++;
	}
	this->current_oversight_point = this->oversight_points.begin();
	concatenate_reverse_list(this->oversight_points);
}
void UxV_Vessel::set_sector_id_oversight(int id) {
	this->sector_id_oversight = id;
}
void UxV_Vessel::set_recovery_activation(bool act) { this->recovery_activation = act; }

#endif