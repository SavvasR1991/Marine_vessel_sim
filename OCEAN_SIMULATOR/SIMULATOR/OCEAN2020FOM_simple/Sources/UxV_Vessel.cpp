#include "UxV_Vessel.h"
#include "Tracking_Shadowing_Mode.h"
#include "Surveilance_Loiter_Mode.h"
#include "Navigation_Jobs.h"
#include "UxV_Vessel_Helper_functions.h"

//[1]
/***************** ElementVessel ****************/
UxV_Vessel::UxV_Vessel(VESSEL_INIT_DATA vessel_data, DtExerciseConn* myExConn,char comments,char logs,char log_tim, std::vector<Area_Obstacle>* team_status, std::map<std::string, SHADOWING_TEAM*> *teams_shadowing_status, std::map<std::string, SHADOWING_TEAM*> *teams_shadowing_status_sub, std::map<int, bool>* sector_surface_status_available, std::map<int, bool>* sector_subwater_status_available, std::map<int, std::vector<Dt3dPoint>>* sector_surface_status, std::map<int, std::vector<Dt3dPoint>>* sector_subwater_status, int jam_timer)
{
	print_color_message("\n------- New team vessel creation "+ vessel_data .name +" ------------\n", COLOR_TEXT::MAIN_TITLE_CYAN);
	std::fstream movement_output;
	double x_dep, y_dep , x_reset, y_reset;

	this->logs_timer = log_tim;
	this->log_dir_timer = vessel_data.log_dir_timer;

	//******************* REFERENCES *****************//
	this->kinematics_status = new VESSEL_KINEMATICS();
	this->vessel_char = new VESSEL_CHARACTERISTICS();
	this->vessel_motion = new VESSEL_MOTION_VALUES();
	this->collision_avoidance_detector = new Collision_Avoidance();
	this->fom_event_evaluator = new FOM_EVENT(vessel_data.name);
	this->obstacle_status = team_status;
	this->sector_surface_status_available = sector_surface_status_available;
	this->sector_subwater_status_available = sector_subwater_status_available;
	this->sector_surface_status = sector_surface_status;
	this->sector_subwater_status = sector_subwater_status;

	//******************* CONNECTION ******************//
	this->exConn = myExConn;							//Vessel connection
	this->comments = comments;
	this->logs = logs;

	//******************* ATTRIBUTES ******************//
	this->set_Vessel_data(vessel_data);

	//************ SET VESSEL'S PATROLING CHUNKS ******//
	this->create_Patroling_Points(vessel_data, x_dep, y_dep, x_reset, y_reset);

	//******** KINIMATICS VESSEL'S ATTRIBUTES *********//
	this->set_Vessel_kinematics_init(vessel_data, x_dep, y_dep, x_reset, y_reset);

	this->vessel_motion->set_acceleration(0.0);
	this->vessel_motion->set_acceleration_comp_x(0.0);
	this->vessel_motion->set_acceleration_comp_y(0.0);
	this->vessel_motion->set_acceleration_comp_z(0.0);

	this->vessel_motion->set_speed(0.0);
	this->vessel_motion->set_speed_comp_x(0.0);
	this->vessel_motion->set_speed_comp_y(0.0);
	this->vessel_motion->set_speed_comp_z(0.0);

	//************ SET VESSEL'S TYPE *****************//
	if (vessel_char->get_type() == "SUB_ROV") {			//**** SUBWATER TYPE ****//
		create_Vessel_Subwater(teams_shadowing_status_sub);
	}
	else if (vessel_char->get_type() == "SURFACE") {		//**** SURFACE TYPE ****//
		create_Vessel_Surface(teams_shadowing_status);
	}
	else {
		std::cout << "ERROR in" << vessel_char->get_name() << " this vessel type is not supported" << std::endl;
		exit(-1);
	}

	this->total_ticks = 0;
	this->total_time = 0;

	this->vangared_ticks = 0;
	this->vangured_time = 0;

	this->locked_ticks = 0;
	this->locked_time = 0;

	this->locked_ticks_2 = 0;
	this->locked_time_2 = 0;

	this->oversigh_ticks = 0;
	this->oversigh_time = 0;

	this->survilance_ticks = 0;
	this->survilance_time = 0;

	this->jam_ticks = 0;
	this->jam_time = 0;

	this->reassignment_ticks = 0;
	this->reassignment_time = 0;

	this->average_distanc_fr_target = 0;
	this->average_distanc_fr_target2 = 0;

	this->jam_timer = jam_timer;

	this->reassignment_activation = false;

	if (this->logs == 'y') {
		movement_output.open(log_dir + "\\" + vessel_char->get_name() + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
		movement_output << "0: " << setprecision(12) << this->kinematics_status->get_current_x() << ", " << setprecision(12) << this->kinematics_status->get_current_y() << ", " << setprecision(12) << this->kinematics_status->get_current_z() << " {" << this->kinematics_status->get_current_theta_horizontal() << ", " << this->kinematics_status->get_current_theta_vertical() << "} ->";
		movement_output << " " << setprecision(12) << this->kinematics_status->get_destination_x() << ", " << setprecision(12) << this->kinematics_status->get_destination_y() << ", " << setprecision(12) << this->kinematics_status->get_destination_z() << "\n";
		movement_output.close();
	}

	if (this->logs_timer == 'y') {
		movement_output.open(log_dir_timer + "\\" + vessel_char->get_name() + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
		movement_output << "----------------------------- VESSEL DATA ---------------------------------- \n";
		movement_output << "VESSEL NAME: "<< this->getName()<<"\n";
		movement_output << "VESSEL TYPE: "<< this->getType()<<"\n";
		movement_output << "\n";
		movement_output << "VESSEL LENGTH    : " << this->get_length()<< " m\n";
		movement_output << "VESSEL WIDTH     : " << this->get_width() << " m\n";
		movement_output << "VESSEL HEIGGHT   : " << this->get_craft() << " m\n";
		movement_output << "VESSEL MASS      : " << this->mass_kg << " kg\n";
		movement_output << "VESSEL MAX SPEED : " << this->vessel_motion->get_Max_speed()*3.6 << " kh/m\n";
		movement_output << "\n";
		movement_output.close();
	}
}

//[2]
/***************** ~ElementVessel ***************/
UxV_Vessel::~UxV_Vessel() {
	std::cout << "\n>>----- " << vessel_char->get_name() << " Deleted -----<<" << std::endl;
	if (this->logs_timer == 'y') {
		std::fstream movement_output;
		movement_output.open(log_dir_timer + "\\" + vessel_char->get_name() + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
		movement_output << "\n";
		movement_output << "----------------------------- VESSEL TIMERS -------------------------------- \n";
		movement_output << "TOTAL TICKS       : " << this->total_ticks << " \n";
		movement_output << "TOTAL EXEC TIME   : " << this->total_time << " secs\n\n";
		movement_output << "------------------------- VESSEL SURVEILANCE ----------------------- \n";
		movement_output << "SURVEILANCE TICKS : " << this->survilance_ticks << " \n";
		movement_output << "SURVEILANCE TIME  : " << this->survilance_time << " secs\n";
		movement_output << "\n";
		if (this->vangared_ticks > 0) {
			movement_output << "------------------------- VESSEL TRACKING -------------------------- \n";
			for (std::vector<std::string>::iterator ccheck = std::begin((target_name_history)); ccheck != std::end(target_name_history); ++ccheck) {
				movement_output << "TARGET NAME                  : " << (*ccheck) << " \n";
			}
			movement_output << "\n";
			movement_output << "VANGUARED DEPLOY             : " << this->vangared_ticks << "\n";
			movement_output << "VANGUARED DEPLOY TIME        : " << this->vangured_time << " secs\n";
			movement_output << "\n";
			if (reassignment_activation) {
				movement_output << "VANGUARED RE-DEPLOY 2        : " << this->reassignment_ticks << "\n";
				movement_output << "VANGUARED RE-DEPLOY TIME 2   : " << this->reassignment_time << " secs\n";
				movement_output << "\n";
			}
			movement_output << "VANGUARED TARGET LOCK TICKS  : " << this->locked_ticks << "\n";
			movement_output << "VANGUARED TARGET LOCK TIME   : " << this->locked_time << " secs\n";
			movement_output << "\n";
			if (reassignment_activation) {
				movement_output << "VANGUARED TARGET LOCK TICKS 2: " << this->locked_ticks_2 << "\n";
				movement_output << "VANGUARED TARGET LOCK TIME  2: " << this->locked_time_2 << " secs\n";
				movement_output << "\n";
			}
			movement_output << "OVERSIGHT PATROLING TICKS    : " << this->oversigh_ticks << "\n";
			movement_output << "OVERSIGHT PATROLING TIME     : " << this->oversigh_time << " secs\n";
			movement_output << "\n";
			if ((this->locked_time + this->vangured_time) > 0) {
				movement_output << "AVERAGE DISTANCE TARGET      : " << (this->average_distanc_fr_target) / (this->locked_time + this->vangured_time) << " m\n\n";
			}
			else {
				movement_output << "AVERAGE DISTANCE TARGET      : " << (this->average_distanc_fr_target) << " m\n\n";
			}
			if (reassignment_activation) {
				if ((this->locked_time_2 + this->reassignment_time) > 0) {
					movement_output << "AVERAGE DISTANCE TARGET 2    : " << (this->average_distanc_fr_target2) / (this->locked_time_2 + this->reassignment_time) << " m\n\n";
				}
				else {
					movement_output << "AVERAGE DISTANCE TARGET 2    : " << (this->average_distanc_fr_target2) / (this->locked_time_2 + this->reassignment_time) << " m\n\n";
				}
			}
			if (this->jam_ticks > 0) {
				movement_output << "------------------------- VESSEL JAM RECOVERY ---------------------- \n";
				movement_output << "JAM RECOVERY TICKS          : " << (this->jam_ticks) << " \n";
				movement_output << "JAM RECOVERY TIME           : " << (this->jam_time) << " secs\n\n";
			}
			movement_output << "----------------------------- VESSEL JOBS PERCENTAGES ---------------------- \n";
			movement_output << "SURVEILANCE            : " << (this->survilance_ticks * 100) / this->total_ticks << " %\n";
			movement_output << "VANGUARED DEPLOY       : " << (this->vangared_ticks * 100) / this->total_ticks << " %\n";
			if (reassignment_activation) {
				movement_output << "VANGUARED RE-DEPLOY 2  : " << (this->reassignment_ticks * 100) / this->total_ticks << " %\n";
			}
			movement_output << "VANGUARED LOCK TARGET  : " << (this->locked_ticks * 100) / this->total_ticks << " %\n";
			if (reassignment_activation) {
				movement_output << "VANGUARED LOCK TARGET 2: " << (this->locked_ticks_2 * 100) / this->total_ticks << " %\n";
			}
			movement_output << "OVERSIGHT              : " << (this->oversigh_ticks * 100) / this->total_ticks << " %\n";
			if (this->jam_ticks > 0)
			{
				movement_output << "JAM RECOVERY           : " << (this->jam_ticks * 100) / this->total_ticks << " %\n\n";
			}
		}
		movement_output.close();
	}
	for (std::list<Point*>::iterator it=this->patroling_points.begin(); it != this->patroling_points.end();++it) {
		delete (*it);
	}
	delete this->vessel_char;
	delete this->kinematics_status;
	delete this->vessel_motion;
	delete this->fom_event_evaluator;
	delete this->collision_avoidance_detector;
	if(this->exConn != NULL) {
		DtDELETE(this->VesselDataTopoView);
	}
	if (this->VesselDataPub != NULL) {
		DtDELETE(this->VesselDataPub);
	}	
}

//[3]
/***************** simVesselTick ****************/
bool UxV_Vessel::VesselsimTick(DtTime dt, std::map<std::string, TEAM_JOB_STATUS*> team_status, std::vector <EVENT*> *event, FOM_EVENT* fom_event, DtTime simTime, int counter_cycle) {
	this->dt = dt;
	this->simTime = simTime;
	this->cycleCounter = counter_cycle;
	this->reset_mode_on = team_status[vessel_char->get_name()]->reset_mode_on;
	this->oversight_mode_on = team_status[vessel_char->get_name()]->oversight_mode_on;
	this->total_ticks++;
	this->total_time += dt;

	if (!this->evaluateEvent(event, fom_event)) {
		std::cout << "ERROR in Vessel:" << vessel_char->get_name() << " event evaluate status" << std::endl;
		return false;
	}
	if (!this->execute(dt)) {
		std::cout << "ERROR in Vessel:" << vessel_char->get_name() << " execute status" << std::endl;
		return false;
	}
	if (!this->publish_possition()) {
		std::cout << "ERROR in Vessel:" << vessel_char->get_name() << " publish possition status" << std::endl;
		return false;
	}
	return true;
}

//[4]
/***************** evaluateEvent ****************/
bool UxV_Vessel::evaluateEvent(std::vector <EVENT*>* event, FOM_EVENT* fom_event) {
	this->fom_event_evaluator->fill_data(fom_event);
	this->waves = false;
	if (this->reset_mode_on) {									// RESET IS ENABLED
		resetVessel_Values();
	}
	else if (this->recovery_activation) {
		this->job = JOB::RECOVERY;
	}
	else if (this->oversight_mode_on) {
		this->job = JOB::OVERSIGHT;
		this->job_previous = JOB::OVERSIGHT;
		this->mode = MODE::TRACKING_SHADOWING;
		if (this->oversight_timer_temp >= this->oversight_timer) {
			if (this->getName() == this->leader_vangared_name) {
				if ((this->sector_id_oversight) >= 0 ) {
					if (this->getType() == "SURFACE") {
						std::map<int, bool>::iterator it = (*(this->sector_surface_status_available)).find((this->sector_id_oversight));
						if (it != (*(this->sector_surface_status_available)).end()) {
							it->second = false;
						}
					}
					else {
						std::map<int, bool>::iterator it = (*(this->sector_subwater_status_available)).find((this->sector_id_oversight));
						if (it != (*(this->sector_subwater_status_available)).end()) {
							it->second = false;
						}
					}
				}
			}
			resetVessel_Values();
		}
		this->oversight_timer_temp++;
	}
	else {	
		if (event == NULL) {
			this->event_message = EVENT_MESSAGE::NO_MESSAGE;
		}
		else{
			evaluate_target_income();
			for (std::vector<EVENT*>::iterator it = std::begin(*(event)); it != std::end(*(event)); ++it) {
				EVENT_MESSAGE incoming_event = (*it)->getEvent();
				if (incoming_event == EVENT_MESSAGE::RESET_VESSELS) {
					evaluate_reset();
					break;
				}
				else if (incoming_event == EVENT_MESSAGE::TARGET_INCOMING) {
					evaluate_target_income();
				}
				else {
					evaluate_no_message();
				}
			}
		}
		
	}	
	return true;
}

//[5]
/***************** execute **********************/
bool UxV_Vessel::execute(DtTime dt) {
	
	/************************** [1] GET ENVIROMENTAL OBSTACLES ************************************/
	this->radar_detection_scanning();

	/************************** [2] SET THE RELEVANT VESSEL'S JOB *********************************/
	this->set_current_job();

	/************************** [3] SET THE RELEVANT VESSEL'S MOVEMENT ****************************/
	this->move_to_possition(dt);

	/************************** [4] CHECK IF VESSEL IS OUT OF STANDARD AREA ***********************/
	this->check_if_out_of_patroling_area();

	return true;
}

//[6]
/***************** publish_possition ************/
bool UxV_Vessel::publish_possition() {

	this->final_possition[0] = this->kinematics_status->get_current_x();
	this->final_possition[1] = this->kinematics_status->get_current_y();
	this->final_possition[2] = this->kinematics_status->get_current_z();

	this->final_orient = DtTaitBryan(DtDeg2Rad(this->kinematics_status->get_current_theta_horizontal()),DtDeg2Rad(0.0), DtDeg2Rad(0.0));
	double psi =DtModPerZero((this->final_orient.psi()), M_2PI);

	this->final_velocity[0] = this->vessel_motion->get_speed_x();
	this->final_velocity[1] = this->vessel_motion->get_speed_y();
	this->final_velocity[2] = 0.0;

	this->final_acceleration[0] = this->vessel_motion->get_acceleration_x();
	this->final_acceleration[1] = this->vessel_motion->get_acceleration_y();
	this->final_acceleration[2] = 0.0;
	
	this->save_print_vessel_possition();

	if (this->getType() != "SURFACE") {
		this->final_possition[2] = -this->kinematics_status->get_current_z();
	}

	if (this->exConn != NULL) {
		try {
			/*cout << this->getName() << " lat:" << this->final_possition[0] << " long:" << this->final_possition[1] << " z:" << this->final_possition[2] << endl;
			cout << "            top:"<< this->VesselDataTopoView->location()<<endl;
			cout << "            lat:" << this->kinematics_status->get_destination_x() << " long:" << this->kinematics_status->get_destination_x() << " z:" << this->final_possition[2] << endl;
			cout << "            psi:" << DtRad2Deg(this->final_orient.psi()) << " phi:" << DtRad2Deg(this->final_orient.phi()) << " the:" << DtRad2Deg(this->final_orient.theta()) << endl;
			cout << "            Vel: " << this->vessel_motion->get_speed() << "m/s, vx:" << final_velocity[0] << " vy:" << final_velocity[1] << " vz:" << final_velocity[2] << endl;
			cout << "            Acc: " << this->vessel_motion->get_acceleration()<< "m/s^2, vx:" << final_acceleration[0] << " vy:" << final_acceleration[1] << " vz:" << final_acceleration[2] << endl << endl;
			*/
			//this->VesselDataTopoView->setAcceleration(this->final_acceleration);
			this->VesselDataTopoView->setLocation(this->final_possition);
			this->VesselDataTopoView->setOrientation(this->final_orient);
			//this->VesselDataTopoView->setVelocity(this->final_velocity);
			//this->VesselDataPub->esr()->printData(); cout << endl;

			this->VesselDataPub->tick();		
		}
		catch (std::exception e) {
			return false;
		}
	}
	return true;
}

//[7]
/***************** set_FOM_disruptions ************/
void UxV_Vessel::set_FOM_disruptions() {
	if (this->fom_event_evaluator->getEvent()) {
		this->waves = true;
		//cout << "---- "<<this->getName();
		//cout << " from:" << this->kinematics_status->get_current_theta_horizontal();
		double dis_vel = this->fom_event_evaluator->get_velocity();
		double new_curr_hor_angle = this->kinematics_status->get_current_theta_horizontal() + this->fom_event_evaluator->get_angle_hor_dis();
		new_curr_hor_angle = angle_degree_normalization(new_curr_hor_angle);
		this->kinematics_status->set_current_theta_horizontal(new_curr_hor_angle);
		if (dis_vel > 0) {
			if (dis_vel + this->vessel_motion->get_acceleration() >= vessel_motion->get_Max_speed()) {
				vessel_motion->set_speed(vessel_motion->get_Max_speed());
				vessel_motion->set_speed_comp_x(vessel_motion->get_Max_speed()*cos(DtDeg2Rad(new_curr_hor_angle)));
				vessel_motion->set_speed_comp_y(vessel_motion->get_Max_speed()*sin(DtDeg2Rad(new_curr_hor_angle)));
				vessel_motion->set_speed_comp_z(0.0);

				vessel_motion->set_acceleration(0.0);
				vessel_motion->set_acceleration_comp_x(0.0);
				vessel_motion->set_acceleration_comp_y(0.0);
				vessel_motion->set_acceleration_comp_z(0.0);
			}
			else {
				this->vessel_motion->set_speed_comp_x(dis_vel*cos(DtDeg2Rad(new_curr_hor_angle)));
				this->vessel_motion->set_speed_comp_y(dis_vel*sin(DtDeg2Rad(new_curr_hor_angle)));
			}
		}
		//cout << "-> to:" << this->kinematics_status->get_current_theta_horizontal() << " dis:"<< this->fom_event_evaluator->get_angle_hor_dis() <<endl;
		this->fom_event_evaluator->cleanFOM_evaluator();


	}
	else {
		this->waves = false;
	}
}

//[8]
/***************** radar_detection_scanning *******/
void UxV_Vessel::radar_detection_scanning() {
	struct Comparison
	{
		bool const operator()(Area_Obstacle lhs, Area_Obstacle rhs) const
		{
			return (lhs).get_distance() < (rhs).get_distance();
		}
	};
	double distance = 0, vel, angle, *vel_p, *angle_p, vel_tar, angle_tar,x_a,y_a,z_a,x_b,y_b,z_b, max_acc, max_angle_speed, max_vel, radius_a, radius_b;

	bool check_flag = false;
	this->obstacles.clear();
	this->obstacles_Kalman_Predicted.clear();

	for (std::vector<Area_Obstacle>::iterator it = std::begin(*(this->obstacle_status)); it != std::end(*(this->obstacle_status)); ++it) {
		if ((it)->get_name() != this->getName()) {
			if (this->getType() == "SURFACE") {
				if ((it)->get_z() >= 0) {
					distance = point_distance(this->get_x(), this->get_y(), (it)->get_x(), (it)->get_y());
					this->obstacles.push_back(Area_Obstacle((it)->get_x(), (it)->get_y(), 0, (it)->get_radius(), distance, (it)->get_name(), (it)->get_velocity(), (it)->get_angle(), (it)->get_flag_1()));
					this->obstacles.back().set_job((it)->get_job());
				}
			}
		}
	}
	if (!(this->obstacles.empty())) {
		sort(this->obstacles.begin(), this->obstacles.end(), Comparison());
		for (std::vector<Area_Obstacle>::iterator it = std::begin((this->obstacles)); it != std::end((this->obstacles)); ++it) {
			vel = vessel_motion->get_speed();
			angle = this->kinematics_status->get_current_theta_horizontal();
			vel_p = &vel;
			angle_p = &angle;
			vel_tar = (it)->get_velocity();
			angle_tar = (it)->get_angle();
			x_a = kinematics_status->get_current_x();
			y_a = kinematics_status->get_current_y();
			z_a = kinematics_status->get_current_z();
			x_b = (it)->get_x();
			y_b = (it)->get_y();
			z_b = (it)->get_z();
			max_acc = vessel_motion->get_Max_deceleration();
			max_angle_speed = vessel_motion->get_Max_angle_speed();
			max_vel = vessel_motion->get_Max_speed();
			radius_a = this->get_length();
			radius_b = (it)->get_radius();

			if (vessel_char->get_type() == "SURFACE") {
				if ((it)->get_name().find("Surface_Target_") != std::string::npos) {
					if (this->mode == MODE::LOITER_SURVEILANCE) {
						if ((it)->get_job() != JOB::PATROLING) {
							Dt3dPoint point_comming;
							point_comming.setX(x_b);
							point_comming.setY(y_b);
							point_comming.setZ(0.0);
							Dt3dPoint point_curr;
							point_curr.setX(x_a);
							point_curr.setY(y_a);
							point_curr.setZ(0.0);
							if (this->sector->PointInSector(point_comming) && this->sector->PointInSector(point_curr)) {
								if (this->collision_avoidance_detector->collision_avoidance_start(vel, angle, vel_tar, angle_tar, x_a, y_a, z_a, x_b, y_b, z_b, radius_b, avoid_distance, max_acc, max_angle_speed, emegercy_avoidance_on, max_vel)) {
									this->kinematics_status->set_current_theta_horizontal(*angle_p);
									vessel_motion->set_speed(*vel_p,*angle_p, 0.0, 0.0);
								}
							}
						}
						else {
							if (this->collision_avoidance_detector->collision_avoidance_start(vel, angle, vel_tar, angle_tar, x_a, y_a, z_a, x_b, y_b, z_b, safe_distance, avoid_distance, max_acc, max_angle_speed, emegercy_avoidance_on, max_vel)) {
								this->kinematics_status->set_current_theta_horizontal(*angle_p);
								vessel_motion->set_speed(*vel_p, *angle_p, 0.0, 0.0);
							}
						}
					}
				}
				else if ((it)->get_name().find("Surfacewater_") != std::string::npos) {
					if (this->mode == MODE::LOITER_SURVEILANCE) {
						if (this->job == JOB::PATROLING) {
							if ((it)->get_job() != JOB::PATROLING) {
								Dt3dPoint point_comming;
								point_comming.setX(x_b);
								point_comming.setY(y_b);
								point_comming.setZ(0.0);
								Dt3dPoint point_curr;
								point_curr.setX(x_a);
								point_curr.setY(y_a);
								point_curr.setZ(0.0);
								if (this->sector->PointInSector(point_comming) && this->sector->PointInSector(point_curr)) {
									if (this->collision_avoidance_detector->collision_avoidance_start(vel, angle, vel_tar, angle_tar, x_a, y_a, z_a, x_b, y_b, z_b, radius_b, avoid_distance, max_acc, max_angle_speed, emegercy_avoidance_on, max_vel)) {
										this->kinematics_status->set_current_theta_horizontal(*angle_p);
										vessel_motion->set_speed(*vel_p, *angle_p, 0.0, 0.0);
									}
								}
							}
						}
					}
				}
				else if ((it)->get_name().find("Shadow_team_") != std::string::npos) {
					if (this->mode == MODE::LOITER_SURVEILANCE) {
						if (this->collision_avoidance_detector->collision_avoidance_start(vel, angle, vel_tar, angle_tar, x_a, y_a, z_a, x_b, y_b, z_b, radius_b, avoid_distance, max_acc, max_angle_speed, emegercy_avoidance_on, max_vel)) {
							this->kinematics_status->set_current_theta_horizontal(*angle_p);
							vessel_motion->set_speed(*vel_p, *angle_p, 0.0, 0.0);
						}
					}
					else {

					}

				}
				else {

				}
			}
			else {

			}
		}
	}
}

//[9]
/************* evaluate_reset *******************/
void UxV_Vessel::evaluate_reset() {
	this->resetVessel_Values();
}

//[10]
/************* evaluate_target_income ***********/
void UxV_Vessel::evaluate_target_income() {
	std::vector<SHADOWING_TEAM_DATA*> *current_list;
	bool check_if_is_voted = false;
	for (std::map<std::string, SHADOWING_TEAM*>::iterator it_shadow = std::begin(*(this->teams_shadowing_status)); it_shadow != std::end(*(this->teams_shadowing_status)); ++it_shadow) {
		current_list = (*it_shadow).second->get_shadow_team();
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin((*current_list)); it2 != std::end(*current_list); ++it2) {
			if (this->getName() == (*it2)->get_name()) {
				if (this->detected_target == false) {
					this->job = JOB::VANGUARED;
					this->job_previous = JOB::VANGUARED;
				}
				check_if_is_voted = true;
				this->my_team_shawdowing_voted = current_list;
				this->leader_vangared_name = (*it2)->get_vessel_name_leader();
				if (this->getName() == leader_vangared_name) {
					this->shadow_team_leader = true;
				}
				else {
					this->shadow_team_leader = false;
				}
				this->team_id_shadow = (*it2)->get_id();
				this->target_X = (*it2)->get_X_target();
				this->target_Y = (*it2)->get_Y_target();
				this->target_Z = (*it2)->get_Z_target();
				this->detected_target = true;
				this->mode = MODE::TRACKING_SHADOWING;
				this->event_message = EVENT_MESSAGE::TARGET_INCOMING;

				bool target_exists = false;
				for (std::vector<std::string>::iterator ccheck = std::begin((target_name_history)); ccheck != std::end(target_name_history); ++ccheck) {
					if ((*ccheck) == "TARGET_0" + to_string(this->team_id_shadow)) {
						target_exists = true;
					}
				}
				if (!target_exists) {
					if (target_name_history.size() > 0) {
						this->reassignment_activation = true;
					}
					target_name_history.push_back("TARGET_0" + to_string(this->team_id_shadow));
				}

				break;
			}
		}
		if (check_if_is_voted == true) {
			break;
		}
	}
	if (check_if_is_voted == false) {
		check_if_is_voted = false;
		this->my_team_shawdowing_voted = NULL;
		this->detected_target = false;
		this->target_X = 0;
		this->target_Y = 0;
		this->target_Z = 0;
		this->resetVessel_Values();
		this->mode = MODE::LOITER_SURVEILANCE;
		this->job = JOB::PATROLING;
		this->job_previous = JOB::PATROLING;
		this->event_message = EVENT_MESSAGE::NO_MESSAGE;
		this->reset_mode_on = false;
	}
}

//[11]
/************* evaluate_no_message ***************/
void UxV_Vessel::evaluate_no_message() {
	this->event_message = EVENT_MESSAGE::NO_MESSAGE;
}

//[12]
/************* set_current_job *******************/
void UxV_Vessel::set_current_job() {
	switch (this->job) {
		case JOB::PATROLING:	
			Surveilance_Loiter::patroling(kinematics_status, vessel_char,vessel_motion, current_patroling_point, patroling_points);
			this->survilance_ticks++;
			this->survilance_time += this->dt;
			break;
		case JOB::RESET:	 
			Surveilance_Loiter::reset(kinematics_status, vessel_char, current_patroling_point, patroling_points, &reset_mode_on, &this->job);
			if (jam_timer <= 0) {
				this->survilance_ticks++;
				this->survilance_time += this->dt;
			}
			else {
				this->jam_ticks++;
				this->jam_time+= this->dt;
			}
			break;
		case JOB::VANGUARED:  
			Tracking_Shadowing::vanguared(kinematics_status, vessel_char, this->target_X, this->target_Y, this->target_Z, this->my_team_shawdowing_voted, &this->job, this->vanguard_distance, this->vanguared_Distance_sub_depth);
			if (!reassignment_activation) {
				this->vangared_ticks++;
				this->vangured_time += this->dt;
				if (point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z()) <= 2 * this->ship_range)
					this->average_distanc_fr_target += point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z());
			}
			else {
				this->reassignment_ticks++;
				this->reassignment_time += this->dt;
				if (point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z()) <= 2 * this->ship_range)
					this->average_distanc_fr_target2 += point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z());
			}
			break;
		case JOB::LOCK:		  
			Tracking_Shadowing::lock(kinematics_status, vessel_char, this->target_X, this->target_Y, this->target_Z, this->my_team_shawdowing_voted, &this->job, &this->team_is_locked, this->vanguard_distance, this->vanguared_Distance_sub_depth);	
			if (!reassignment_activation) {
				this->locked_ticks++;
				this->locked_time += this->dt;
				if (point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z()) <= 2 * this->ship_range)
					this->average_distanc_fr_target += point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z());
			}
			else {
				this->locked_ticks_2++;
				this->locked_time_2 += this->dt;
				if (point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z()) <= 2 * this->ship_range)
					this->average_distanc_fr_target2 += point_distance_3d(this->target_X, this->target_Y, this->target_Z, this->kinematics_status->get_current_x(), this->kinematics_status->get_current_y(), this->kinematics_status->get_current_z());
			}
			break;
		case JOB::OVERSIGHT: 
			Tracking_Shadowing::oversight(kinematics_status, vessel_char, current_oversight_point, oversight_points, this->leader_vangared_name, this->x_leader_overview, this->y_leader_overview, this->z_leader_overview);		
			this->oversigh_ticks++;
			this->oversigh_time += this->dt;
			break;
		case JOB::RECOVERY:   break;
		default:			  this->job = JOB::NONE;
	}
}

//[13]
/************* move_to_possition ******************/
void UxV_Vessel::move_to_possition(DtTime dt) {

	this->angle_balancing_equalizer();
	this->speed_balancing_equalizer(); 

	//KINMATICS WAVES
	this->set_FOM_disruptions();

	this->move();

	this->update_mode();
}

//[14]
/************* move_to_possition ******************/
void UxV_Vessel::check_if_out_of_patroling_area() {
	Dt3dPoint curr_poss;
	curr_poss.setX(kinematics_status->get_current_x());
	curr_poss.setY(kinematics_status->get_current_y());
	curr_poss.setZ(kinematics_status->get_current_z());
	this->out_of_area = !(this->sector->PointInSector(curr_poss));
}