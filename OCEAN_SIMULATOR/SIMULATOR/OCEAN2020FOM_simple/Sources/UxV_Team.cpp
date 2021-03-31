#include "UxV_Team.h"
#include "Reassignment_Shadow_team.h"
#include "UxV_Team_Helper_functions.h"

//[1]
/***************** UxV_Team *********************/
UxV_Team::UxV_Team(TEAM_INIT_DATA team_init_data, DtExerciseConn* myExConn,	char commnents, char commnents_basic, char logs, char logs_FOMS, char logs_Kalman, char logs_metrics, std::string log_dir, std::string log_dir_field, std::string log_dir_timers, std::string log_dir_Kalman_Filter, std::string log_dir_metric)
{
	this->commnents_basic = commnents_basic;
	this->Ship_Activated = team_init_data.Ship_Activated;
	this->logs_metrics = logs_metrics;
	this->log_dir_metrics = log_dir_metric;
	set_up_logs_paths(commnents, logs, logs_FOMS, logs_Kalman, log_dir, log_dir_field, log_dir_timers, log_dir_Kalman_Filter);	//Set up logs paths
	initialize_team_attributes(team_init_data, myExConn);									//initialize teams attributes
	deploy_UxV_vessels();
}

//[2]
/************ ~UxV_Team *************************/
UxV_Team::~UxV_Team()
{
	print_color_message("\n[1] UxV_Team deleted\n", COLOR_TEXT::GREEN_COLOR);
	for (std::vector<UxV_Vessel*>::iterator it = std::begin(team); it != std::end(team); ++it) {
		delete (*it);
	}

	print_color_message("\n[2] Target deleted\n", COLOR_TEXT::GREEN_COLOR);
	for (std::vector<Target*>::iterator it = std::begin(targets); it != std::end(targets); ++it) {
		delete (*it);
	}

	print_color_message("\n[3] Team shadow Deletion\n", COLOR_TEXT::GREEN_COLOR);
	if (!this->teams_shawdowing.empty()) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it) {
			delete (it->second);
		}
		this->teams_shawdowing.empty();
	}

	print_color_message("\n[4] Team shadow Deletion subwater\n", COLOR_TEXT::GREEN_COLOR);
	if (!this->teams_shawdowing_sub.empty()) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing_sub); it != std::end(this->teams_shawdowing_sub); ++it) {
			delete (it->second);
		}
		this->teams_shawdowing_sub.empty();
	}

	print_color_message("\n[5] UxV_Team status list deleted: Sectors deleted\n", COLOR_TEXT::GREEN_COLOR);
	for (std::map<std::string, TEAM_JOB_STATUS*>::iterator it = std::begin(team_status); it != std::end(team_status); ++it) {
		delete (it->second);
	}
}

//[3]
/************ deploy_UxV_vessels ****************/
void UxV_Team::deploy_UxV_vessels() {
	std::string jammed_vessel;
	if (this->Jamming_time_start>0) {
		jammed_vessel = "NKUA_USV_0" + to_string(this->Jamming_Activate);
	}
	std::fstream ship_log, ship_log_sub;
	std::fstream element_attributes;
	this->print_count = 0;
	int current_uxv_subwater = this->uxv_subwater, current_uxv_surface = this->uxv_surface;
	std::string vessel_name, vessel_type, blank_leader = "no_leader";
	this->bomb_activated = false;

	this->refLatitude_init = 0.0;
	this->refLongitude_init = 0.0;
	double refHeight_init = 0;

	if (this->logs == 'y') {
		ship_log.open(log_dir + "\\ship_log_surface.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		if (this->uxv_subwater > 0) {
			ship_log_sub.open(log_dir + "\\ship_log_subwater.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		}
		element_attributes.open(log_dir + "\\element_attributes.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	}

	/******************** CREATE VESSELS **********************************/
	if (this->commnents_basic == 'y') {
		print_color_message("\n\n--------------- UxV_Team: creating Vessels ---------------------\n", COLOR_TEXT::MAIN_TITLE_GREEN);
	}
	int sub_counter = 0, sur_counter = 0;

	if (this->targets_num > 0) {
		if (this->targets_num <= 3) {
			if (this->target_z_1 < 0) {
				vessel_name = "UUV_TAR_1";
				vessel_type = "SUB_ROV";
			}
			else {
				vessel_name = "USV_TAR_1";
				vessel_type = "SURFACE";
			}
			Target *element = new Target(this->myExConn, vessel_name, vessel_type, this->target_x_1, this->target_y_1, this->target_z_1, this->target_velocity_1, this->target_angle_1, 0.0, this->target_start_time_1, 1, this->target_is_a_bomb_1, this->log_dir, this->refLatitude, this->refLongitude);
			element->set_turning_status(target_turning_point_1_1, target_turning_point_2_1, target_turning_point_3_1, target_turning_point_4_1, target_turning_point_5_1, target_turning_point_6_1, target_turning_point_7_1, target_turning_point_8_1, target_turning_point_9_1, target_turning_point_10_1, target_turning_angle_1);
			targets.push_back(element);
		}

		if (this->targets_num <= 3 && this->targets_num > 1) {
			if (this->target_is_a_bomb_2 <= 1) {
				if (this->target_z_2 < 0) {
					vessel_name = "UUV_TAR_2";
					vessel_type = "SUB_ROV";
				}
				else {
					vessel_name = "USV_TAR_2";
					vessel_type = "SURFACE";
				}
				Target *element = new Target(this->myExConn, vessel_name, vessel_type, this->target_x_2, this->target_y_2, this->target_z_2, this->target_velocity_2, this->target_angle_2, 0.0, this->target_start_time_2, 2, this->target_is_a_bomb_2, this->log_dir, this->refLatitude, this->refLongitude);
				element->set_turning_status(target_turning_point_1_2, target_turning_point_2_2, target_turning_point_3_2, target_turning_point_4_2, target_turning_point_5_2, target_turning_point_6_2, target_turning_point_7_2, target_turning_point_8_2, target_turning_point_9_2, target_turning_point_10_2, target_turning_angle_2);
				targets.push_back(element);
			}
			else {
				vessel_name = "MINE_NKUA_2";
				vessel_type = "SUB_ROV";
				Target *element = new Target(this->myExConn, vessel_name, vessel_type, this->target_x_1, this->target_y_1, this->target_z_1, this->target_velocity_1, this->target_angle_1, 0.0, this->target_start_time_2, 2, this->target_is_a_bomb_2, this->log_dir, this->refLatitude, this->refLongitude);
				targets.push_back(element);
			}

		}
		if (this->targets_num == 3) {
			if (this->target_is_a_bomb_3 <= 1) {
				if (this->target_z_2 < 0) {
					vessel_name = "UUV_TAR_3";
					vessel_type = "SUB_ROV";
				}
				else {
					vessel_name = "USV_TAR_3";
					vessel_type = "SURFACE";
				}
				Target *element = new Target(this->myExConn, vessel_name, vessel_type, this->target_x_3, this->target_y_3, this->target_z_3, this->target_velocity_3, this->target_angle_3, 0.0, this->target_start_time_3, 3, this->target_is_a_bomb_3, this->log_dir, this->refLatitude, this->refLongitude);
				element->set_turning_status(target_turning_point_1_3, target_turning_point_2_3, target_turning_point_3_3, target_turning_point_4_3, target_turning_point_5_3, target_turning_point_6_3, target_turning_point_7_3, target_turning_point_8_3, target_turning_point_9_3, target_turning_point_10_3, target_turning_angle_3);
				targets.push_back(element);
			}
			else {
				vessel_name = "MINE_NKUA_3";
				vessel_type = "SUB_ROV";
				Target *element = new Target(this->myExConn, vessel_name, vessel_type, this->target_x_1, this->target_y_1, this->target_z_1, this->target_velocity_1, this->target_angle_1, 0.0, this->target_start_time_3, 3, this->target_is_a_bomb_3, this->log_dir, this->refLatitude, this->refLongitude);
				targets.push_back(element);
			}
		}

	}
	
	for (int i = 0; i < this->uxv_num; i++) {
		VESSEL_INIT_DATA vessel_data;
		int jam_timer = -100;
		if (current_uxv_subwater != 0) {								//set sub vessel attributes
			vessel_name = "NKUA_UUV_0" + std::to_string(current_uxv_subwater);
			vessel_type = "SUB_ROV";
			vessel_data.id_type = current_uxv_subwater;
			current_uxv_subwater--;
			vessel_data.acceleration_decent = this->MAX_SUBMERSION_SPEED_sub;
			vessel_data.length = this->uxv_length_sub;
			vessel_data.width = this->uxv_width_sub;
			vessel_data.height = this->uxv_heigth_sub;
			vessel_data.sensor_range = this->uxv_sensor_range_sub;
			vessel_data.angle_speed = this->angle_speed_sub;
			vessel_data.acceleration = this->ACCELERATION_sub;
			vessel_data.deceleration = this->DECELERATION_sub;
			vessel_data.maximum_speed = this->MAXIMUM_SPEED_sub;
			vessel_data.refHeight = this->refHeight;
			vessel_data.maximum_speed_submersion = this->MAX_SUBMERSION_SPEED_sub;
			vessel_data.vanguard_distance = this->vanguared_distance_sub;
			vessel_data.sector = this->create_Sectors(sub_counter, this->uxv_subwater, this->refHeight,this->ship_range);
			vessel_data.mass = this->mass_kg_sub;
			vessel_data.vanguared_Distance_sub_depth = this->vanguared_Distance_sub_depth;
			sub_counter++;
		}
		else {															//set sur vessel attributes
			vessel_name = "NKUA_USV_0" + std::to_string(current_uxv_surface) + "";
			vessel_type = "SURFACE";
			vessel_data.id_type = current_uxv_surface;
			current_uxv_surface--;
			vessel_data.length = this->uxv_length_sur;
			vessel_data.width = this->uxv_width_sur;
			vessel_data.height = this->uxv_heigth_sur;
			vessel_data.sensor_range = this->uxv_sensor_range_sur;
			vessel_data.angle_speed = this->angle_speed_sur;
			vessel_data.acceleration = this->ACCELERATION_sur;
			vessel_data.deceleration = this->DECELERATION_sur;
			vessel_data.maximum_speed = this->MAXIMUM_SPEED_sur;
			vessel_data.refHeight = 0;
			vessel_data.sector = this->create_Sectors(sur_counter, this->uxv_surface, 0.0, this->ship_range);
			vessel_data.vanguard_distance = this->vanguared_distance_sur;
			vessel_data.mass = this->mass_kg_sur;
			vessel_data.vanguared_Distance_sub_depth = 0.0;
			sur_counter++;
		}


		vessel_data.avoid_distance = this->safe_distance;
		vessel_data.avoid_distance = this->avoid_distance;
		vessel_data.name = vessel_name;//extented attribute
		if (jammed_vessel == vessel_data.name) {
			jam_timer = this->Jamming_Activate;
		}
		vessel_data.type = vessel_type;
		vessel_data.team_id = this->team_id; //extented attribute
		vessel_data.ship_range = this->ship_range;
		vessel_data.oversight_timer = this->oversight_timer;

		vessel_data.refLatitude = this->refLatitude_init;
		vessel_data.refLongitude = this->refLongitude_init;
		vessel_data.deploy_latitude = this->refLatitude_init;
		vessel_data.deploy_longitude = this->refLongitude_init;
		vessel_data.deploy_latitude_INIT = this->refLatitude;
		vessel_data.deploy_longitude_INIT = this->refLongitude;

		vessel_data.sensor_depth_range = this->uxv_sensor_depth_range;
		vessel_data.log_dir = this->log_dir;
		vessel_data.log_dir_timer = this->log_dir_metrics;
		vessel_data.logs_Kalman = this->logs_Kalman;
		vessel_data.log_dir_Kalman_Filter = this->log_dir_Kalman_Filter;

		//************* Initialize vessel deploy x, y, z
		double xt, yt;
		double cx = vessel_data.sector->getA()->x(), cy = vessel_data.sector->getA()->y();
		double bx = vessel_data.sector->getB()->x(), by = vessel_data.sector->getB()->y();
		double ax = vessel_data.sector->getC()->x(), ay = vessel_data.sector->getC()->y();

		get_point_by_relevant_radius(ax, ay, bx, by, cx, cy, vessel_data.width, xt, yt);

		/******************** CREATE VESSELS OBJECTS **************************/
		UxV_Vessel *element = new UxV_Vessel(vessel_data, this->myExConn, this->commnents, this->logs, this->logs_metrics, &(this->obstacle_status), &(this->teams_shawdowing), &(this->teams_shawdowing_sub), &(this->sector_surface_status_available), &(this->sector_subwater_status_available),&(this->sector_surface_status), &(this->sector_subwater_status), jam_timer);

		/******************** CREATE VESSELS STATUS MAP ***********************/
		TEAM_JOB_STATUS* element_status = new TEAM_JOB_STATUS();
		element_status->node_jobs_status = 'P';
		element_status->name = vessel_name;
		element_status->type = vessel_type;
		element_status->current_latitude = this->refLatitude;
		element_status->current_longitude = this->refLongitude;
		element_status->current_Height = this->refHeight;
		element_status->deploy_latitude = element->get_deploy_x();
		element_status->deploy_longitude = element->get_deploy_y();
		element_status->deploy_Height = element->get_deploy_z();
		element_status->areaSector = vessel_data.sector;
		element_status->reset_mode_on = false;
		element_status->oversight_mode_on = false;
		element->setSector(element_status->areaSector);

		team_status[element_status->name] = element_status;
		team.push_back(element);
		if (this->logs == 'y') {
			if (vessel_type == "SURFACE") {
				ship_log << element_status->areaSector->toString();
			}
			else {
				ship_log_sub << element_status->areaSector->toString();
			}
		}
	}

	this->refLatitude = refLatitude_init;
	this->refLongitude = refLongitude_init;

	if (this->commnents_basic == 'y') {
		print_color_message("\n-------- UxV_Team: creating Shadow team --------------\n", 10);	//create shadow team
	}
	int counter = 0;
	for (std::vector<UxV_Vessel*>::iterator it = std::begin(team); it != std::end(team); ++it) {
		this->team_shadowing_summary.push_back(new SHADOWING_TEAM_DATA(0, (*it)->get_scanning_radius(), (*it)->getName(), (*it)->getType(), blank_leader, false, 0, (*it)->get_radius(), counter, JOB::VANGUARED, this->commnents_basic));
		this->team_shadowing_summary.back()->update_shadow_member((*it)->get_deploy_x(), (*it)->get_deploy_y(), (*it)->get_deploy_z(), 0, 0, 0, 0, 0);
		counter++;
	}

	if (this->logs == 'y') {
		element_attributes << "Ship range                   : " + std::to_string(this->ship_range) + " meters\n";
		element_attributes << "Ship uxv underwater vessels  : " + std::to_string(this->uxv_subwater) + "\n";
		element_attributes << "Ship uxv surface vessels     : " + std::to_string(this->uxv_surface) + "\n";
		element_attributes << "Ship reference coordinates   : [" + double_to_string(this->refLatitude) + "," + double_to_string(this->refLongitude) + ",0]\n\n";
		element_attributes << "Ship surface vessels radius  : " + std::to_string(2 * this->uxv_length_sur) + "\n";
		element_attributes << "Ship subwater vessels radius : " + std::to_string(2 * this->uxv_length_sub) + "\n";

		element_attributes.close();
		ship_log.close();
		ship_log_sub.close();
	}

	this->create_central_main_ship();
}

//[4]
/********** evaluate_FOM_income *****************/
void UxV_Team::evaluate_FOM_income(Water_Waves_Kinematics* enviromental_elements) {
	if (enviromental_elements != NULL) {
		store_water_waves_log(enviromental_elements);

		double vessel_x = 0, vessel_y = 0, vessel_z = 0, vessel_hor_angle = 0, vessel_ver_angle = 0, vessel_vel = 0, vessel_mass = 0,angle_vel_h = 0, angle_vel_v = 0, B = 0, L = 0, T = 0;
		std::string vessel_type;
		int uxv_counter = 0;
		for (std::vector<UxV_Vessel*>::iterator it = std::begin(team); it != std::end(team); ++it)
		{
			vessel_x = (*it)->get_x();
			vessel_y = (*it)->get_y();
			vessel_z = (*it)->get_z();
			vessel_hor_angle = (*it)->get_current_kinematics()->get_current_theta_horizontal();
			vessel_ver_angle = (*it)->get_reference_angle_vertical();
			vessel_vel = (*it)->get_linear_velocity();
			vessel_type = (*it)->getType();
			vessel_vel = (*it)->get_linear_velocity();
			vessel_mass = (*it)->get_mass();
			angle_vel_h = (*it)->get_angular_velocity();
			angle_vel_v = (*it)->get_angular_velocity();
			B = (*it)->get_length();
			L = (*it)->get_width();
			T = (*it)->get_craft();
			
			enviromental_elements->set_enviromental_disruption_for_point((*it)->getName(),this->fom_event[uxv_counter], vessel_x, vessel_y, vessel_z,vessel_hor_angle, vessel_ver_angle, vessel_vel, angle_vel_h, angle_vel_v, vessel_type,B, L, T, vessel_mass, B, this->cycleCounter);
			uxv_counter++;
		}		
	}
}

//[5]
/********** start_team_cycle ********************/
void UxV_Team::start_team_cycle(DtTime dt, std::vector <EVENT*> *event, DtTime simTime, Water_Waves_Kinematics *enviromental_elements) {
	
	if (this->commnents_basic == 'y') {
		std::cout << "\n- Cycle tick [" << this->cycleCounter << "]" << std::endl;
	}
	else {
		if (this->cycleCounter == 1) {
			std::cout << "\nRunning Test..";
		}
		if (this->cycleCounter == (print_count * 60 + 1)) {
			std::cout << ".";
			this->print_count++;
		}
	}
	this->team_event = event;

	this->evaluate_event(dt);
	this->evaluate_FOM_income(enviromental_elements);
	this->create_obstacle_enviroment();
	this->update_vessels(dt, simTime);
	this->cycleCounter++;
}

//[6]
/********** evaluate_event **********a************/
void UxV_Team::evaluate_event(DtTime dt) {
	if (this->targets.size() > 0) {
		double area = 5;
		double xb = 0, yb = 0, zb = 0;
		for (std::vector<Target*>::iterator it = std::begin(targets); it != std::end(targets); ++it)
		{
			(*it)->VesselsimTick(this->cycleCounter, dt);
			if ((*it)->get_turning_probability() <= 1) {
				this->team_event->push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, (*it)->get_id(), (*it)->get_x(), (*it)->get_y(), (*it)->get_z(), (*it)->get_angle_hor(), (*it)->get_vel(), area, "no_vessel"));
			}
			else {
				if ((*it)->get_turning_probability() <= this->cycleCounter) {
					this->team_event->push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, (*it)->get_id(), (*it)->get_x(), (*it)->get_y(), (*it)->get_z(), (*it)->get_angle_hor(), (*it)->get_vel(), area, "no_vessel"));
				}
			}
		}
		
	}
	if (!(*this->team_event).empty()) {
		targets_id.clear();
		for (std::vector<EVENT*>::iterator it = std::begin(*(this->team_event)); it != std::end(*(this->team_event)); ++it) {
			if ((*it)->getEvent() == EVENT_MESSAGE::RESET_VESSELS) {
				if (this->commnents_basic == 'y') {
					print_color_message("------ RESET TEAM POSSITIONS \n", 12);
				}
				this->targets_available = false;
				this->tasks_available = false;
				for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it = this->team_status.begin(); it != team_status.end(); ++it) {
					it->second->reset_mode_on = true;
				}
				break;
			}
			else if ((*it)->getEvent() == EVENT_MESSAGE::TARGET_INCOMING) {
				if (point_is_in_range(this->refLatitude_init, this->refLongitude_init, (*it)->getX(), (*it)->getY(), this->ship_range)) {
					if (this->commnents_basic == 'y') {
						print_color_message("------ TARGET INCOMING (" + to_string((*it)->getID()) + ") -> {" + to_string((*it)->getX()) + "," + to_string((*it)->getY()) + "," + to_string((*it)->getZ()) + "} \n", 14);
					}
					this->targets_available = true;
					targets_id.push_back(TARGET_STATS((*it)->getX(), (*it)->getY(), (*it)->getZ(), (*it)->getVelocity(), (*it)->getAngle(), (*it)->getRadius(), (*it)->getID()));
					if (targets_id_history.find((*it)->getID()) == targets_id_history.end()) {
						targets_id_history.insert({ (*it)->getID(),(TARGET_STATS((*it)->getX(),(*it)->getY(),(*it)->getZ(),(*it)->getVelocity(),(*it)->getAngle(),(*it)->getRadius(),(*it)->getID())) });
					}
					else {
						for (std::map<int, TARGET_STATS>::iterator ist = std::begin(targets_id_history); ist != std::end(targets_id_history); ++ist) {
							if (ist->first == (*it)->getID()) {
								(ist)->second.set_xyx((*it)->getX(), (*it)->getY(), (*it)->getZ());
								break;
							}
						}
					}
				}
			}
			else {
				this->targets_available = false;
				this->tasks_available = false;
			}
		}
		if (!targets_id.empty()) {
			this->update_Possition_Predictor();
			voting_shadow_team_deployment();
		}
		else {
			reset_team_shadowing_status();
		}
	}
	else {
		reset_team_shadowing_status();
	}
}

//[7]
/********** voting_shadow_team_deployment *******/
void UxV_Team::voting_shadow_team_deployment() {
	voting_shadow_team_update_surface();
	created_shadow_team_surface();
	voting_shadow_team_update_subwater();
	created_shadow_team_subwater();
}

//[8]
/********** voting_shadow_team_update_surface ***/
void UxV_Team::voting_shadow_team_update_surface() {
	std::string target_name, v_name,leader_now;
	std::vector<SHADOWING_TEAM_DATA*> *curr_team = NULL;
	std::map<std::string, SHADOWING_TEAM*>::iterator it = this->teams_shawdowing.begin();
	bool team_checked = false;
	double xc = 0, yc = 0, zc = 0, x_leader = 0, y_leader = 0, xt = 0,yt = 0,zt = 0, xll = 0,yll = 0;
	int sector_id = 0, segments = 0, counter = 0, target_id = 0;

	while (it != this->teams_shawdowing.end())
	{
		team_checked = false;
		curr_team = ((it)->second->get_shadow_team());
		for (std::vector<TARGET_STATS>::iterator itt = std::begin(this->targets_id); itt != std::end(this->targets_id); ++itt) {
			if (curr_team->at(0)->get_id() == (itt)->id) {
				team_checked = true;
				break;
			}
		}
		if (team_checked == false) {
			leader_now = (curr_team)->at(0)->get_vessel_name_leader();
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
				for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
					if ((it_stat)->first == (*it_summ)->get_name()) {
						it_stat->second->oversight_mode_on = true;
						for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_check = std::begin(this->team_shadowing_summary); it_check != std::end(this->team_shadowing_summary); ++it_check) {
							if ((*it_check)->get_name() == (it_stat)->first) {
								if ((*it_check)->get_vessel_name_leader() == (it_stat)->first) {
									target_id = (*it_check)->get_id();
									xll = (*it_check)->get_X();
									yll = (*it_check)->get_Y();

								}

								(*it_check)->set_availability(true);
								(*it_check)->vote_leader(false);
								(*it_check)->set_vessel_name_leader("no_leader");
								(*it_check)->set_id(0);
								v_name = (*it_check)->get_name();
								xc = this->team_status[v_name]->current_latitude;
								yc = this->team_status[v_name]->current_longitude;
								zc = this->team_status[v_name]->current_Height;
								(*it_check)->update_shadow_member(xc, yc, zc, xc, yc, zc, 0, 0);
								break;
							}
						}
						break;
					}
				}
			}
			for (std::map<int, TARGET_STATS>::iterator ist = std::begin(targets_id_history); ist != std::end(targets_id_history); ++ist) {
				if (ist->first == target_id) {
					xt = (ist)->second.x;
					yt = (ist)->second.y;
					break;
				}
			}
			sector_id = point_in_sector(xt, yt, this->sector_surface_status, this->sector_surface_status_available);
			if (sector_id < 0) {
				sector_id = point_in_sector(xll, yll, this->sector_surface_status, this->sector_subwater_status_available);
			}
			if (sector_id < 0) {
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
					for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
						if ((it_stat)->first == (*it_summ)->get_name()) {
							it_stat->second->oversight_mode_on = false;
							it_stat->second->reset_mode_on = true;
						}
					}
				}
			}
			else {
				segments = curr_team->size() - 1;
				counter = 0;
				std::vector<Dt3dPoint> temp_sector = this->sector_surface_status[sector_id];
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
					for (std::vector<UxV_Vessel*>::iterator itUxV_Vessel = std::begin(team); itUxV_Vessel != std::end(team); ++itUxV_Vessel)
					{
						if ((*itUxV_Vessel)->getName() == (*it_summ)->get_name()) {

							(*itUxV_Vessel)->set_oversight_mode_on(true);
							if ((*itUxV_Vessel)->getName() == leader_now) {
								(*itUxV_Vessel)->set_xy_leader_overview((temp_sector.at(0).x() + temp_sector.at(1).x()) / 2, (temp_sector.at(0).y() + temp_sector.at(1).y()) / 2);
								(*itUxV_Vessel)->set_sector_id_oversight(sector_id);
							}
							else {
								std::vector<double> xx;
								std::vector<double> yy;
								oversight_segment_calculator(temp_sector.at(1).x(), temp_sector.at(1).y(), temp_sector.at(0).x(), temp_sector.at(0).y(), counter, segments, xx, yy);
								(*itUxV_Vessel)->set_xy_oversight(xx, yy);
								(*itUxV_Vessel)->set_sector_id_oversight(sector_id);
								counter++;
							}
							(*itUxV_Vessel)->set_z_leader_overview(0.0);
							break;
						}
					}
				}
			}
			curr_team->clear();
			it = this->teams_shawdowing.erase(it);
		}
		else {
			++it;
		}
	}
	check_if_vessels_is_jammed();
}

//[9]
/********** voting_shadow_team_update_subwater **/
void UxV_Team::voting_shadow_team_update_subwater() {
	std::string target_name, v_name, leader_now;
	std::vector<SHADOWING_TEAM_DATA*> *curr_team = NULL;
	std::map<std::string, SHADOWING_TEAM*>::iterator it = this->teams_shawdowing_sub.begin();
	bool team_checked = false;
	double xc = 0, yc = 0, zc = 0, x_leader = 0, y_leader = 0, xt=0, yt = 0, zt = 0;
	int sector_id = 0, segments = 0, counter = 0, target_id = 0;
	double xll = 0, yll = 0;
	while (it != this->teams_shawdowing_sub.end())
	{
		team_checked = false;
		curr_team = ((it)->second->get_shadow_team());
		for (std::vector<TARGET_STATS>::iterator itt = std::begin(this->targets_id); itt != std::end(this->targets_id); ++itt) {
			if (curr_team->at(0)->get_id() == (itt)->id) {
				team_checked = true;
				break;
			}
		}
		if (team_checked == false) {
			leader_now = (curr_team)->at(0)->get_vessel_name_leader();
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
				for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
					if ((it_stat)->first == (*it_summ)->get_name()) {
						it_stat->second->oversight_mode_on = true;
						for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_check = std::begin(this->team_shadowing_summary); it_check != std::end(this->team_shadowing_summary); ++it_check) {
							if ((*it_check)->get_name() == (it_stat)->first) {
								if ((*it_check)->get_vessel_name_leader() == (it_stat)->first) {
									target_id = (*it_check)->get_id();
									xll = (*it_check)->get_X();
									yll = (*it_check)->get_Y();

								}
								(*it_check)->set_availability(true);
								(*it_check)->vote_leader(false);
								(*it_check)->set_vessel_name_leader("no_leader");
								(*it_check)->set_id(0);
								v_name = (*it_check)->get_name();
								xc = this->team_status[v_name]->current_latitude;
								yc = this->team_status[v_name]->current_longitude;
								zc = this->team_status[v_name]->current_Height;
								(*it_check)->update_shadow_member(xc, yc, zc, xc, yc, zc, 0, 0);
								break;
							}
						}
						break;
					}
				}
			}
			for (std::map<int, TARGET_STATS>::iterator ist = std::begin(targets_id_history); ist != std::end(targets_id_history); ++ist) {
				if (ist->first == target_id) {
					xt = (ist)->second.x;
					yt = (ist)->second.y;
					zt = (ist)->second.z;
					break;
				}
			}
			sector_id = point_in_sector(xt, yt, this->sector_subwater_status, this->sector_subwater_status_available);
			if (sector_id < 0) {
				sector_id = point_in_sector(xll, yll, this->sector_subwater_status, this->sector_subwater_status_available);
			}
			if (sector_id < 0) {
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
					for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
						if ((it_stat)->first == (*it_summ)->get_name()) {
							it_stat->second->oversight_mode_on = false;
							it_stat->second->reset_mode_on = true;
						}
					}
				}
			}
			else {
				segments = curr_team->size() - 1;
				counter = 0;
				std::vector<Dt3dPoint> temp_sector = this->sector_subwater_status[sector_id];
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
					for (std::vector<UxV_Vessel*>::iterator itUxV_Vessel = std::begin(team); itUxV_Vessel != std::end(team); ++itUxV_Vessel)
					{
						if ((*itUxV_Vessel)->getName() == (*it_summ)->get_name()) {
							(*itUxV_Vessel)->set_oversight_mode_on(true);
							if ((*itUxV_Vessel)->getName() == leader_now) {
								(*itUxV_Vessel)->set_xy_leader_overview((temp_sector.at(0).x() + temp_sector.at(1).x()) / 2, (temp_sector.at(0).y() + temp_sector.at(1).y()) / 2);
								(*itUxV_Vessel)->set_sector_id_oversight(sector_id);
								(*itUxV_Vessel)->set_z_leader_overview(zt);
							}
							else {
								std::vector<double> xx;
								std::vector<double> yy;
								oversight_segment_calculator(temp_sector.at(1).x(), temp_sector.at(1).y(), temp_sector.at(0).x(), temp_sector.at(0).y(), counter, segments, xx, yy);
								(*itUxV_Vessel)->set_xy_oversight(xx, yy);
								(*itUxV_Vessel)->set_sector_id_oversight(sector_id);
								(*itUxV_Vessel)->set_z_leader_overview(zt);
								counter++;
							}
							break;
						}
					}
				}
			}
			curr_team->clear();
			it = this->teams_shawdowing_sub.erase(it);
		}
		else {
			++it;
		}
	}
}

//[10]
/********** created_shadow_team_surface *********/
void UxV_Team::created_shadow_team_surface() {

	std::string target_name, shadow_team_type = "SURFACE";
	double vanguared_distance = this->vanguared_distance_sur;

	for (std::vector<TARGET_STATS>::iterator it = std::begin((this->targets_id)); it != std::end((this->targets_id)); ++it) {
		bool created = false, is_reassignment_required = false;
		target_name = "Surface_Target_" + to_string((it)->id);
		if (this->teams_shawdowing.find(target_name) == this->teams_shawdowing.end()) {
			this->teams_shawdowing.insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
			created = this->teams_shawdowing[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, this->ship_shadowing_team, this->team_shadowing_summary, shadow_team_type, this->commnents_basic);
			if (!created) {
				this->teams_shawdowing.erase(target_name);
			}
			is_reassignment_required = Reassignment_Shadow_Team::shadow_team_reassignment_required(this->team_shadowing_summary, this->targets_id);
			if (is_reassignment_required) {
				Reassignment_Shadow_Team::vessel_reassignment_performance(&this->teams_shawdowing, &this->team_shadowing_summary, this->targets_id, this->refLatitude, this->refLongitude, this->commnents_basic);
			}
		}
		else {
			this->teams_shawdowing[target_name]->update_target_to_team((it)->x, (it)->y, (it)->z, (it)->vel, (it)->ang, this->team_status, this->team_shadowing_summary, this->commnents_basic);
			int shadow_team_members = this->teams_shawdowing[target_name]->get_shadow_team()->size(), direction = 0;
			double xBeforeRotation = 0, yBeforeRotation = 0, radius_event = (it)->radius;

			std::vector<SHADOWING_TEAM_DATA*> * curr_array = (this->teams_shawdowing[target_name]->get_shadow_team());
			if ((it)->x >= this->refLatitude) {  // right
				direction = 1;					// clockwise
			}
			else { // left
				direction = 0;					// counterclockwise
			}

			double new_y = 0;
			int first = 0, second = 0, third = 0, fourth = 0;
			if ((it)->y >= this->refLongitude) { // Top
				double amgle_new = angle_between_2d_points(refLatitude, refLongitude, (it)->x, (it)->y);
				double dist_new = point_distance(refLatitude, refLongitude, (it)->x, (it)->y);
				double vertical = dist_new * sin(degrees_to_radians(amgle_new));
				double theta_rad = degrees_to_radians(270);
				new_y = this->refLongitude + vertical * sin(theta_rad);
				first = 1;
				second = 0;
				third = 3;
				fourth = 2;
			}
			else {								// Bottom
				new_y = (it)->y;
				first = 0;
				second = 1;
				third = 2;
				fourth = 3;
			}
			if (shadow_team_members == 2) {
				if (curr_array->at(0)->get_shadow_id() == 0) {
					xBeforeRotation = (it)->x - (curr_array->at(0)->get_radius() + vanguared_distance) * cos(degrees_to_radians(315));
					yBeforeRotation = new_y + (curr_array->at(0)->get_radius() + vanguared_distance) * sin(degrees_to_radians(315));
					curr_array->at(0)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(1)->get_shadow_id() == 1) {
					xBeforeRotation = (it)->x + (curr_array->at(1)->get_radius() + vanguared_distance) * cos(degrees_to_radians(45));
					yBeforeRotation = new_y + (curr_array->at(1)->get_radius() + vanguared_distance) * sin(degrees_to_radians(45));
					curr_array->at(1)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
			else if (shadow_team_members == 3) {
				if (curr_array->at(0)->get_shadow_id() == 0) {
					xBeforeRotation = (it)->x - (curr_array->at(0)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y;
					curr_array->at(0)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}

				if (curr_array->at(1)->get_shadow_id() == 1) {
					xBeforeRotation = (it)->x + (curr_array->at(1)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y;
					curr_array->at(1)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}

				if (curr_array->at(2)->get_shadow_id() == 2) {
					xBeforeRotation = (it)->x;
					yBeforeRotation = new_y + (curr_array->at(2)->get_radius() + vanguared_distance);
					curr_array->at(2)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
			else if (shadow_team_members == 4) {
				if (curr_array->at(first)->get_shadow_id() == first) {
					xBeforeRotation = (it)->x - (curr_array->at(first)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y + radius_event;
					curr_array->at(first)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(second)->get_shadow_id() == second) {
					xBeforeRotation = (it)->x + (curr_array->at(second)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y + radius_event;
					curr_array->at(second)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(third)->get_shadow_id() == third) {
					xBeforeRotation = (it)->x - (curr_array->at(third)->get_radius() + vanguared_distance) + radius_event;
					yBeforeRotation = new_y + (curr_array->at(third)->get_radius() + vanguared_distance);
					curr_array->at(third)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(fourth)->get_shadow_id() == fourth) {
					xBeforeRotation = (it)->x + (curr_array->at(fourth)->get_radius() + vanguared_distance) - radius_event;
					yBeforeRotation = new_y + (curr_array->at(fourth)->get_radius() + vanguared_distance);
					curr_array->at(fourth)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
		}
	}
}

//[11]
/********** created_shadow_team_subwater ********/
void UxV_Team::created_shadow_team_subwater() {

	std::string target_name, shadow_team_type;
	std::vector<SHADOWING_TEAM_DATA*> *curr_team = NULL;
	std::map<std::string, SHADOWING_TEAM*>::iterator it = this->teams_shawdowing_sub.begin();
	bool team_checked = false;
	double vanguared_distance = this->vanguared_distance_sub;
	shadow_team_type = "SUB_ROV";
	double xc = 0, yc = 0, zc = 0;
	std::string v_name;

	while (it != this->teams_shawdowing_sub.end())
	{
		team_checked = false;
		curr_team = ((it)->second->get_shadow_team());
		for (std::vector<TARGET_STATS>::iterator itt = std::begin(this->targets_id); itt != std::end(this->targets_id); ++itt) {
			if (curr_team->at(0)->get_id() == (itt)->id) {
				team_checked = true;
				break;
			}
		}

		if (team_checked == false) {
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*curr_team); it_summ != std::end(*curr_team); ++it_summ) {
				for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
					if ((it_stat)->first == (*it_summ)->get_name()) {
						it_stat->second->oversight_mode_on = true;
						for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_check = std::begin(this->team_shadowing_summary); it_check != std::end(this->team_shadowing_summary); ++it_check) {
							if ((*it_check)->get_name() == (it_stat)->first) {
								(*it_check)->set_availability(true);
								(*it_check)->vote_leader(false);
								(*it_check)->set_vessel_name_leader("no_leader");
								(*it_check)->set_id(0);
								v_name = (*it_check)->get_name();
								xc = this->team_status[v_name]->current_latitude;
								yc = this->team_status[v_name]->current_longitude;
								zc = this->team_status[v_name]->current_Height;
								(*it_check)->update_shadow_member(xc, yc, zc, xc, yc, zc, 0, 0);
								break;
							}
						}
						break;
					}
				}
			}
			curr_team->clear();
			it = this->teams_shawdowing_sub.erase(it);
		}
		else {
			++it;
		}
	}

	for (std::vector<TARGET_STATS>::iterator it = std::begin((this->targets_id)); it != std::end((this->targets_id)); ++it) {
		bool created = false, is_reassignment_required = false;
		target_name = "Surface_Target_" + to_string((it)->id);
		if (this->teams_shawdowing_sub.find(target_name) == this->teams_shawdowing_sub.end()) {
			this->teams_shawdowing_sub.insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
			created = this->teams_shawdowing_sub[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, this->ship_shadowing_team, this->team_shadowing_summary, shadow_team_type, this->commnents_basic);
			if (!created) {
				this->teams_shawdowing_sub.erase(target_name);
			}
			is_reassignment_required = Reassignment_Shadow_Team::shadow_team_reassignment_required(this->team_shadowing_summary, this->targets_id);
			if (is_reassignment_required) {
				Reassignment_Shadow_Team::vessel_reassignment_performance_sub(&this->teams_shawdowing_sub, &this->team_shadowing_summary, this->targets_id, this->refLatitude, this->refLongitude, this->commnents_basic);
			}
		}
		else {
			this->teams_shawdowing_sub[target_name]->update_target_to_team((it)->x, (it)->y, (it)->z, (it)->vel, (it)->ang, this->team_status, this->team_shadowing_summary, this->commnents_basic);
			int shadow_team_members = this->teams_shawdowing_sub[target_name]->get_shadow_team()->size(), direction = 0;
			double xBeforeRotation = 0, yBeforeRotation = 0, radius_event = (it)->radius;
			std::vector<SHADOWING_TEAM_DATA*> * curr_array = (this->teams_shawdowing_sub[target_name]->get_shadow_team());
			if ((it)->x >= this->refLatitude) {  // right
				direction = 1;					// clockwise
			}
			else { // left
				direction = 0;					// counterclockwise
			}

			double new_y;
			int first, second, third, fourth;
			if ((it)->y >= this->refLongitude) { // Top
				double amgle_new = angle_between_2d_points(refLatitude, refLongitude, (it)->x, (it)->y);
				double dist_new = point_distance(refLatitude, refLongitude, (it)->x, (it)->y);
				double vertical = dist_new * sin(degrees_to_radians(amgle_new));
				double theta_rad = degrees_to_radians(270);
				new_y = this->refLongitude + vertical * sin(theta_rad);
				first = 1;
				second = 0;
				third = 3;
				fourth = 2;
			}
			else {								// Bottom
				new_y = (it)->y;
				first = 0;
				second = 1;
				third = 2;
				fourth = 3;
			}

			if (shadow_team_members == 1) {
				if (curr_array->at(0)->get_shadow_id() == 0) {
					xBeforeRotation = (it)->x;
					yBeforeRotation = (it)->y;
					curr_array->at(0)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, -1);
				}
			}
			else if (shadow_team_members == 2) {
				if (curr_array->at(0)->get_shadow_id() == 0) {
					xBeforeRotation = (it)->x - (curr_array->at(0)->get_radius() + vanguared_distance) * cos(degrees_to_radians(315));
					yBeforeRotation = new_y + (curr_array->at(0)->get_radius() + vanguared_distance) * sin(degrees_to_radians(315));
					curr_array->at(0)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(1)->get_shadow_id() == 1) {
					xBeforeRotation = (it)->x + (curr_array->at(1)->get_radius() + vanguared_distance) * cos(degrees_to_radians(45));
					yBeforeRotation = new_y + (curr_array->at(1)->get_radius() + vanguared_distance) * sin(degrees_to_radians(45));
					curr_array->at(1)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
			else if (shadow_team_members == 3) {
				if (curr_array->at(0)->get_shadow_id() == 0) {
					xBeforeRotation = (it)->x - (curr_array->at(0)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y;
					curr_array->at(0)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(1)->get_shadow_id() == 1) {
					xBeforeRotation = (it)->x + (curr_array->at(1)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y;
					curr_array->at(1)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(2)->get_shadow_id() == 2) {
					xBeforeRotation = (it)->x;
					yBeforeRotation = new_y + (curr_array->at(2)->get_radius() + vanguared_distance);
					curr_array->at(2)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
			else if (shadow_team_members == 4) {
				if (curr_array->at(first)->get_shadow_id() == first) {
					xBeforeRotation = (it)->x - (curr_array->at(first)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y + radius_event;
					curr_array->at(first)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(second)->get_shadow_id() == second) {
					xBeforeRotation = (it)->x + (curr_array->at(second)->get_radius() + vanguared_distance);
					yBeforeRotation = new_y + radius_event;
					curr_array->at(second)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(third)->get_shadow_id() == third) {
					xBeforeRotation = (it)->x - (curr_array->at(third)->get_radius() + vanguared_distance) + radius_event;
					yBeforeRotation = new_y + (curr_array->at(third)->get_radius() + vanguared_distance);
					curr_array->at(third)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
				if (curr_array->at(fourth)->get_shadow_id() == fourth) {
					xBeforeRotation = (it)->x + (curr_array->at(fourth)->get_radius() + vanguared_distance) - radius_event;
					yBeforeRotation = new_y + (curr_array->at(fourth)->get_radius() + vanguared_distance);
					curr_array->at(fourth)->set_coord_BeforeRotation(xBeforeRotation, yBeforeRotation, direction);
				}
			}
		}
	}
}

//[12]
/********** create_obstacle_enviroment **********/
void UxV_Team::create_obstacle_enviroment() {
	int number = 1, name_v = -1;
	double longest_distance = 0, area = 0, radius = 0, x = 0, y = 0, xt = 0, yt = 0, zt = 0, theta_hor_t = 0, vt = 0, distance = 0, cur_distance = 0;
	bool lock_verified = false;
	this->obstacle_status.clear();
	for (std::vector<UxV_Vessel*>::iterator it = std::begin(team); it != std::end(team); ++it)
	{
		if ((*it)->getJob() != JOB::LOCK) {
			this->obstacle_status.push_back(Area_Obstacle((*it)->get_x(), (*it)->get_y(), (*it)->get_z(), (*it)->get_length(), 0, (*it)->getName(), (*it)->get_linear_velocity(), (*it)->get_current_kinematics()->get_current_theta_horizontal(), this->team_status[(*it)->getName()]->out_of_area));
			this->obstacle_status.back().set_job((*it)->getJob());
		}
	}

	if (this->team_event != NULL) {
		for (std::vector<EVENT*>::iterator it = std::begin(*(this->team_event)); it != std::end(*(this->team_event)); ++it) {
			if ((*it)->getEvent() == EVENT_MESSAGE::TARGET_INCOMING) {
				if (point_is_in_range((*it)->getX(), (*it)->getY(), this->refLatitude,this->refLongitude, this->ship_range)) {
					std::string target_name = "Target_Incoming_" + to_string((*it)->getID());
					this->obstacle_status.push_back(Area_Obstacle((*it)->getX(), (*it)->getY(), (*it)->getZ(), (*it)->getRadius(), 0, target_name, (*it)->getVelocity(), (*it)->getAngle(), false));
				}
			}
		}
	}

	for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it) {
		lock_verified = false;
		distance = -1;
		name_v = -1;
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator itvv = std::begin(*(it)->second->get_shadow_team()); itvv != std::end(*(it)->second->get_shadow_team()); ++itvv)
		{
			if ((*itvv)->get_job() == JOB::LOCK) {
				cur_distance = point_distance((*itvv)->get_X(), (*itvv)->get_Y(), (*itvv)->get_X_target(), (*itvv)->get_Y_target());
				if (distance <= cur_distance) {
					distance = cur_distance;
				}
				lock_verified = true;
				name_v = (*itvv)->get_id();
			}
		}
		if (lock_verified) {
			for (std::vector<Area_Obstacle>::iterator it_obs = std::begin(this->obstacle_status); it_obs != std::end(this->obstacle_status); ++it_obs) {
				if (it_obs->get_name() == "Target_Incoming_" + to_string(name_v)) {
					xt = (it_obs)->get_x();
					yt = (it_obs)->get_y();
					zt = (it_obs)->get_z();
					vt = (it_obs)->get_velocity();
					radius = distance;
					theta_hor_t = (it_obs)->get_angle();
					this->obstacle_status.erase(it_obs);
					this->obstacle_status.push_back(Area_Obstacle(xt, yt, zt, radius, 0, "Shadow_team_" + to_string(name_v), vt, theta_hor_t, false));
					number++;
					break;
				}
			}
		}
	}
}

//[13]
/********** update_vessels **********************/
void UxV_Team::update_vessels(DtTime dt, DtTime simTime) {
	int uxv_counter = 0;
	
	for (std::vector<UxV_Vessel*>::iterator it = std::begin(team); it != std::end(team); ++it)
	{
		if (!(*it)->VesselsimTick(dt, this->team_status, this->team_event, this->fom_event[uxv_counter], simTime, this->cycleCounter)) {
			std::cout << "UxV_Team: Vessel's ERROR in" << (*it)->getName() << std::endl;
			exit(-1);
		}
		else {
			this->team_status[(*it)->getName()]->node_jobs_status = (*it)->getJob();
			this->team_status[(*it)->getName()]->current_latitude = (*it)->get_x();
			this->team_status[(*it)->getName()]->current_longitude = (*it)->get_y();
			this->team_status[(*it)->getName()]->current_Height = (*it)->get_z();
			this->team_status[(*it)->getName()]->reference_angle_horizontal = (*it)->get_reference_angle_horizontal();
			this->team_status[(*it)->getName()]->reference_angle_vertical = (*it)->get_reference_angle_vertical();
			this->team_status[(*it)->getName()]->type = (*it)->getType();
			this->team_status[(*it)->getName()]->reset_mode_on = (*it)->get_reset_mode_on();
			this->team_status[(*it)->getName()]->out_of_area = (*it)->get_out_of_area();
			this->team_status[(*it)->getName()]->oversight_mode_on = (*it)->get_oversight_mode_on();

			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_s = std::begin(this->team_shadowing_summary); it_s != std::end(this->team_shadowing_summary); ++it_s) {
				if ((*it_s)->get_name() == (*it)->getName()) {
					(*it_s)->set_job((*it)->getJob());
					break;
				}
			}

			this->fom_event[uxv_counter]->cleanFOM_evaluator();
		}
		uxv_counter++;
	}

	this->mainShipsimTick();

	this->team_event->clear();
}

//[14]
/********** check_if_vessels_is_jammed ***********/
void UxV_Team::check_if_vessels_is_jammed() {
	std::vector<SHADOWING_TEAM_DATA*> *shadow_team_cleanup = NULL;
	std::string target_name, v_name, leader_now;
	double xc = 0, yc = 0, zc = 0, x_leader = 0, y_leader = 0, xt = 0, yt = 0, zt = 0, xll = 0, yll = 0;

	for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_check = std::begin(this->team_shadowing_summary); it_check != std::end(this->team_shadowing_summary); ++it_check) {
			if (this->cycleCounter == this->Jamming_time_start) {
				std::string jammed_vessel = (*it_check)->get_name();
				if (jammed_vessel == "NKUA_USV_0" + to_string(this->Jamming_Activate)) {
					bool is_jammed_yes = false;
					bool is_leader_jammed_yes = false;
					for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it) {
						for (std::vector<SHADOWING_TEAM_DATA*>::iterator itvv = std::begin(*(it)->second->get_shadow_team()); itvv != std::end(*(it)->second->get_shadow_team()); ++itvv)
						{
							if ((*itvv)->get_name() == jammed_vessel) {
								if (jammed_vessel == (*itvv)->get_vessel_name_leader()) {
									is_leader_jammed_yes = true;
									print_color_message("---> Vessel leader " + (*it_check)->get_name() + " is jammed.. \n", COLOR_TEXT::GRAY_COLOR);
								}
								else {
									print_color_message("---> Vessel " + (*it_check)->get_name() + " is jammed.. \n", COLOR_TEXT::RED_COLOR);
								}
								is_jammed_yes = true;
								break;
							}
						}
					}
					if (is_jammed_yes) {
						int target_id = (*it_check)->get_id();
						(*it_check)->set_availability(true);
						(*it_check)->vote_leader(false);
						(*it_check)->set_vessel_name_leader("no_leader");
						(*it_check)->set_id(0);
						(*it_check)->set_job('R');
						v_name = (*it_check)->get_name();
						xc = this->team_status[v_name]->current_latitude;
						yc = this->team_status[v_name]->current_longitude;
						zc = this->team_status[v_name]->current_Height;
						(*it_check)->update_shadow_member(xc, yc, zc, xc, yc, zc, 0, 0);
						for (std::map < std::string, TEAM_JOB_STATUS*>::iterator it_stat = this->team_status.begin(); it_stat != team_status.end(); ++it_stat) {
							if ((*it_stat).first == jammed_vessel) {
								it_stat->second->reset_mode_on = true;
								break;
							}
						}
						print_color_message("---> Vessel " + to_string(this->Jamming_Activate) + " reseting.. \n", COLOR_TEXT::RED_COLOR);
						for (std::map<std::string, SHADOWING_TEAM*>::iterator it = std::begin(this->teams_shawdowing); it != std::end(this->teams_shawdowing); ++it) {
							if ((it)->first == "Surface_Target_" + to_string(target_id)) {
								shadow_team_cleanup = (it)->second->get_shadow_team();
								int counter = 0;
								for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*shadow_team_cleanup); itt != std::end(*shadow_team_cleanup); ++itt) {
									if ((*itt)->get_name() == (jammed_vessel)) {
										itt = shadow_team_cleanup->erase(itt);
										break;
									}
								}
								for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*shadow_team_cleanup); itt != std::end(*shadow_team_cleanup); ++itt) {
									if (is_leader_jammed_yes) {
										(*itt)->set_vessel_name_leader((*itt)->get_name());
										is_leader_jammed_yes = false;
									}
									(*itt)->set_shadow_id(counter);
									counter++;
									for (std::vector<UxV_Vessel*>::iterator update_vessel = std::begin(team); update_vessel != std::end(team); ++update_vessel){
										if ((*itt)->get_name() == (*update_vessel)->getName()){
											(*update_vessel)->set_jam_time_detonation(this->Jamming_time_start);
											for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_stat = std::begin(this->team_shadowing_summary); it_stat != std::end(this->team_shadowing_summary); ++it_stat) {
												if ((*it_stat)->get_name() == (*update_vessel)->getName()) {
													(*it_stat)->set_job(JOB::VANGUARED);
													this->team_status[(*it_stat)->get_name()]->node_jobs_status = JOB::VANGUARED;
													(*update_vessel)->set_job(JOB::VANGUARED);
													break;
												}
											}
											break;
										}
									}
								}
								break;
							}
						}
						this->Jamming_time_start = -1;
					}
					else {
						print_color_message("---> Vessel " + (*it_check)->get_name() + " is not in shadow team.. \n", COLOR_TEXT::CYAN_COLOR);
					}
					break;
				}
			}
		}
	}
}