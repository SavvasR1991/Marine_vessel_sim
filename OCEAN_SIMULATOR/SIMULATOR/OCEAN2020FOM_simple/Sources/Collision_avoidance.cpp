#include "Collision_avoidance.h"

/******************************* COLLISION_AVOIDANCE.CPP *********************************************************/
// [1]  Collision_Avoidance()							constructor
// [2]  ~Collision_Avoidance()							destructor
// [3]  Collision_Avoidance_Reset()						reset all values
// [4]  set_up()										set up all available values
// [5]  geometrical_values_computation()				calculate all vectors and angles of algorithm
// [6]  check_collision()								check if collision is about to occur
// [7]  motion_rediractor()								choose which movement will be utilized
// [8]  estimation()									create estimation obstacle cycle
// [9]  update()										update new velocity and angle
// [10] collision_avoidance_start()						start collision detector
/******************************* COLLISION_AVOIDANCE.CPP *********************************************************/

//[1]
/************** Collision_Avoidance *************/
Collision_Avoidance::Collision_Avoidance() {
	std::cout << "---- Collision ditector created" << std::endl;
	this->collision_check_evaluation = false;
	this->overtaking_mode = false;
	this->heads_on_mode = false;
	this->crossing_mode = false;
	this->VR = 0;
	this->V0 = 0;
	this->a = 0;
	this->b = 0;
	this->gamma = 0;
	this->VR_Previous = 0;
	this->V0_Previous = 0;
	this->a_Previous = 0;
	this->b_Previous = 0;
	this->D_V_Previous = 0;
	this->fi_Previous = 0;
	this->eccentric_expansion_radius_Previous = 0;
	this->eccentric_expansion_x_Previous = 0;
	this->eccentric_expansion_y_Previous = 0;
	this->New_VR = 0;
	this->acceleration = 0;
	this->angular_velocity = 0;
	this->emegercy_avoidance_val = false;
}

//[2]
/************** Collision_Avoidance *************/
Collision_Avoidance::~Collision_Avoidance() {
	std::cout << "---- Collision ditector deleted" << std::endl;
}

//[3]
/*********** Collision_Avoidance_Reset **********/
void Collision_Avoidance::Collision_Avoidance_Reset() {
	this->emegercy_avoidance_val = false;
	this->collision_check_evaluation = false;
	this->overtaking_mode = false;
	this->heads_on_mode = false;
	this->crossing_mode = false;
	this->VR = 0;
	this->V0 = 0;
	this->a = 0;
	this->b = 0;
	this->theta = 0;
	this->fi = 0;
	this->lamda = 0;
	this->gamma = 0;
	this->psi = 0;
	this->dist = 0;
	this->eccentric_expansion_radius = 0;
	this->eccentric_expansion_x = 0;
	this->eccentric_expansion_y = 0;
	this->angular_velocity = 0;

	this->dist_previous = 0;
	this->VR_Previous = 0;
	this->V0_Previous = 0;
	this->a_Previous = 0;
	this->b_Previous = 0;
	this->D_V_Previous = 0;
	this->fi_Previous = 0;
	this->eccentric_expansion_radius_Previous = 0;
	this->eccentric_expansion_x_Previous = 0;
	this->eccentric_expansion_y_Previous = 0;
}

bool Collision_Avoidance::check_range_estimator(double x_a, double y_a, double obs_x, double obs_y, double diss) {
	this->dist = point_distance_3d(x_a, y_a, 0, obs_x, obs_y, 0);
	if ((this->dist) < (diss)) {
		return true;
	}
	else {
		return false;
	}
}

void Collision_Avoidance::set_initial_movements(double v_a, double theta_a, double v_b, double theta_b) {
	this->V0 = v_a;
	this->a = degrees_to_radians(angle_degree_normalization(theta_a));
	this->VR = v_b;
	this->b = degrees_to_radians(angle_degree_normalization(theta_b));
	this->ANGLE_INITIAL = theta_a;
}

void Collision_Avoidance::set_vessel_possition(double x_a, double y_a, double z_a) {
	this->x_a = x_a;
	this->y_a = y_a;
	this->z_a = z_a;
}

void Collision_Avoidance::set_obstacle_possition(double x_b, double y_b, double z_b) {
	this->x_b = x_b;
	this->y_b = y_b;
	this->z_b = z_b;
	this->obs_x = x_b;
	this->obs_y = y_b;
}

void Collision_Avoidance::set_areas(double safe_distance, double avoid_distance)
{
	this->safe_distance = 2*safe_distance;
	this->avoidance_distance = avoid_distance;
	this->radius_b = safe_distance;
}

void Collision_Avoidance::set_velocities_movements(double acceleration, double angular_speed, double max_speed) {
	this->acceleration = acceleration;
	this->ANGLUAL_ORIGINAL = angular_speed;
	this->angular_velocity = 0;
	this->max_speed = max_speed;
}

/***************** check_collision **************/
void Collision_Avoidance::check_encounter_collision_situation() {
	double a_ = radians_to_degrees(this->a);
	double b_ = radians_to_degrees(this->b);
	if (fabs(a_ - b_) < 0.5) {
		this->overtaking_mode = true;
		this->crossing_mode = false;
		this->heads_on_mode = false;
	}
	else if (fabs(a_ - b_) <= 180.5 && fabs(a_ - b_) >= 179.5) {
		this->overtaking_mode = false;
		this->crossing_mode = false;
		this->heads_on_mode = true;
	}
	else {
		this->overtaking_mode = false;
		this->crossing_mode = true;
		this->heads_on_mode = false;
	}
}

//[5]
/********** geometrical_values_computation ******/
void Collision_Avoidance::geometrical_values_computation() {

	double Delta_V = 0;
	double Delta_VR = 0;
	double Delta_V0 = 0;
	double Delta_a = 0;
	double Delta_b = 0;

	this->D_V = sqrt((this->VR*this->VR) + (this->V0*this->V0) -(2 * this->VR*this->V0*cos(this->a - this->b)));
	this->h = asin((this->VR * sin(this->b - this->a)) / this->D_V);
	this->fi = asin((-(this->V0 * sin(this->a - this->b))) / this->D_V);
	this->lamda = degrees_to_radians(180 - (radians_to_degrees(this->h) + radians_to_degrees(this->fi)));
	this->theta = degrees_to_radians(
		angle_degree_normalization(angle_between_2d_points(this->x_a, this->y_a, this->x_b, this->y_b)));
	
	double var_1 = this->VR*sin(this->a - this->theta) - this->V0*sin(this->b - this->theta);
	double var_2 = this->VR*cos(this->a - this->theta) - this->V0*cos(this->b - this->theta);
	this->gamma = atan((var_1) / (var_2));

	this->psi = degrees_to_radians(radians_to_degrees(this->a) - radians_to_degrees(this->fi));
	this->dist = point_distance_3d(this->x_a, this->y_a, 0, this->x_b, this->y_b, 0);
	double hypotinusa = sqrt((this->radius_b / 2)*(this->radius_b / 2) + dist * dist);
	this->m = acos(dist / hypotinusa);

	Delta_a = abs(abs(this->a) - abs(this->a_Previous));
	Delta_b = abs(abs(this->b) - abs(this->b_Previous));
	Delta_VR = abs(abs(this->VR) - abs(this->VR_Previous));
	Delta_V0 = abs(abs(this->V0) - abs(this->V0_Previous));

	if (this->D_V <= 0) {
		this->D_gamma = 0;
	}
	else {
		this->D_gamma = ((sin(this->fi) / D_V) * Delta_VR) + (((this->VR*cos(this->fi)) / D_V) * Delta_a) +
						((-sin(this->h) / D_V) * Delta_V0) + (((this->V0*cos(this->fi)) / D_V) * Delta_b);
	}
}

//[7]
/***************** motion_rediractor ************/
void Collision_Avoidance::motion_rediractor() {
	if (this->heads_on_mode) {
		this->gamma = 0;
		this->D_gamma = 0;
		this->zetta = (this->psi + PI / 2);
	}
	else if (this->overtaking_mode) {
		this->gamma = 0;
		this->D_gamma = 0;
		this->zetta = (this->psi - PI / 2);
	}
	else {
		double a_ = radians_to_degrees(this->a);
		double psi_ = radians_to_degrees(this->theta);
		if (a_ >= psi_) { this->zetta = (this->psi + PI / 2);	}
		else {			  this->zetta = (this->psi - PI / 2);	}
	}
}

//[8]
void Collision_Avoidance::eccentric_expansion_circle() {
	double DCPA = this->dist * sin(fabs(this->gamma));
	double TCPA = (this->dist * cos(fabs(this->gamma))) / this->D_V;
	this->M_DCPA = 0;
	this->M_TCPA = 0;
	double t1 = 0, t2 = 0;

	if (DCPA <= this->safe_distance) {
		M_DCPA = 1; 
	}
	else if (DCPA <= this->avoidance_distance) {
		M_DCPA = (1 / 2 - 1 / 2 * (sin((PI / (this->avoidance_distance - this->safe_distance)) * (DCPA - ((this->avoidance_distance + this->safe_distance) / 2)))));
	}
	else {
		M_DCPA = 0;
	}

	t1 = (DCPA <= this->safe_distance)      ? sqrt((this->safe_distance*this->safe_distance - DCPA * DCPA) / (this->D_V))           : 0;
	t2 = (DCPA <= this->avoidance_distance) ? sqrt((this->avoidance_distance*this->avoidance_distance - DCPA * DCPA) / (this->D_V)) : 0;
	if (TCPA <= t1) {
		M_TCPA = 1; 
	}
	else if (TCPA <= t2) { 
		if (fabs(t1 - t2) < 0.0005) {
			M_TCPA = (t2 - TCPA) / (t2 - t1);
		}
		else {
			M_TCPA = 1;
		}
	}
	else {
		M_TCPA = 0; 
	}
	
	this->collision_propability = (std::min((M_DCPA + M_TCPA) / 2, double(1)));
	if (this->collision_propability <= 0) { this->collision_propability = 0.0; }
	this->eccentric_expansion_radius = 3 * this->avoidance_distance * (double)(1.0 + 2.0 / 3.0 * sin((PI / 2) * (this->collision_propability + 2)));
	this->eccentric_expansion_x = this->x_b + (this->eccentric_expansion_radius - this->avoidance_distance)*cos(this->zetta);
	this->eccentric_expansion_y = this->y_b + (this->eccentric_expansion_radius - this->avoidance_distance)*sin(this->zetta);
	this->x_b = this->eccentric_expansion_x;
	this->y_b = this->eccentric_expansion_y;
	this->radius_b = this->eccentric_expansion_radius;

	this->VR_Previous = this->VR;
	this->V0_Previous = this->V0;
	this->a_Previous = this->a;
	this->b_Previous = this->b;
	this->fi_Previous = this->fi;
	this->dist_previous = this->dist;
}

void Collision_Avoidance::estimate_collision() {
	double ddg = radians_to_degrees(this->D_gamma);
	double dm = radians_to_degrees(this->m);
	double dg = radians_to_degrees(this->gamma);
	if (dg > 0) {
		if (dg >= dm - ddg) {
			this->collision_check_evaluation = false;
		}
		else {
			this->collision_check_evaluation = true;
		}
	}
	else {
		if (dg <= -dm - ddg) {
			this->collision_check_evaluation = false;
		}
		else {
			this->collision_check_evaluation = true;
		}
	}

	if(this->collision_check_evaluation = true) {
		if (this->angular_velocity >= this->ANGLUAL_ORIGINAL) {
			this->angular_velocity = this->ANGLUAL_ORIGINAL;
			this->collision_check_evaluation = false;
		}
		else {
			this->angular_velocity++;
		}

		double a_ = this->ANGLE_INITIAL;
		double b_ = radians_to_degrees(this->theta);
		if (this->heads_on_mode) {
			this->a = a_+ this->angular_velocity;
		}
		else if (this->overtaking_mode) {
			this->a = a_ - this->angular_velocity;
		}
		else {
			this->a = (a_ <= b_) ? (a_ - this->angular_velocity) : (a_ + this->angular_velocity);
		}
		this->a = angle_degree_normalization(this->a);	
		this->a = degrees_to_radians(this->a);
	}
}

//[9]
/***************** update ***********************/
void Collision_Avoidance::update(double &v_a, double &theta_a) {
	if (this->V0 <= 0) {
		this->emegercy_avoidance_val = true;
	}
	if (this->emegercy_avoidance_val) {
		v_a = v_a + this->acceleration;
		if (v_a > this->max_speed) {
			v_a = max_speed;
		}
		theta_a = radians_to_degrees(this->b) - 90;
		theta_a = angle_degree_normalization(theta_a);
	}
	else {
		theta_a = angle_degree_normalization(radians_to_degrees(this->a));
	}
}

//[10]
/*********** collision_avoidance_start ***********/
bool Collision_Avoidance::collision_avoidance_start(double &v_a,double &theta_a,double v_b,double theta_b,double x_a,double y_a,double z_a,double x_b, double y_b,double z_b, double safe_distance,double avoid_distance,double acceleration,double angular_speed,bool &emegercy_mode,double max_speed)
{
	Collision_Avoidance_Reset();
	this->emegercy_avoidance_val = emegercy_mode;

	set_initial_movements(v_a, theta_a, v_b, theta_b);
	set_vessel_possition(x_a, y_a, z_a);
	set_obstacle_possition(x_b, y_b, z_b);
	set_areas(safe_distance, avoid_distance);
	set_velocities_movements(acceleration, angular_speed, max_speed);

	this->collision_check_evaluation = true;
	while (this->collision_check_evaluation) {
		if (check_range_estimator(x_a, y_a, x_b, y_b, avoid_distance) == true) {
			check_encounter_collision_situation();
			geometrical_values_computation();
			motion_rediractor();
			eccentric_expansion_circle();
			estimate_collision();
		}
		else {
			emegercy_avoidance_val = false;
			emegercy_mode = false;
			Collision_Avoidance_Reset();
			return false;
		}
	}
	update(v_a, theta_a);
	emegercy_mode = this->emegercy_avoidance_val;

	return true;
}

void Collision_Avoidance::check_eccentric_expansion(double &x, double &y, double &r) {
	x = this->eccentric_expansion_x;
	y = this->eccentric_expansion_y;
	r = this->eccentric_expansion_radius;
}

void Collision_Avoidance::print_Collision_Values() {
	std::cout << "---------- Print Colission Values ----------------"
		<< "\n- gamma = " << radians_to_degrees(this->gamma)
		<< "\n- Dgamma = " << radians_to_degrees(this->D_gamma)
		<< "\n- m =" << radians_to_degrees(this->m)
		<< "\n- theta = " << radians_to_degrees(this->theta)
		<< "\n- distance =" << dist
		<< "\n- Avoid dis =" << avoidance_distance
		<< "\n- Angular speed =" << angular_velocity
		<< "\n- collision_propability =" << collision_propability
		<< "\n- D V =" << D_V
		<< "\n- a = " << radians_to_degrees(this->a) << endl;
	if (this->heads_on_mode)   { std::cout << "- MODE: HEADS ON MODE\n"; }
	if (this->overtaking_mode) { std::cout << "- MODE: OVERTAKING MODE\n"; }
	if (this->crossing_mode)   { std::cout << "- MODE: CROSSING MODE\n"; }

	std::cout << "- EXP_X: " << this->eccentric_expansion_x
		 << "\n- EXP_Y: " << this->eccentric_expansion_y
		 << "\n- EXP_RADIUS:" << this->eccentric_expansion_radius << endl;

	std::cout << endl;
}

void Collision_Avoidance::print_Values() {
	std::cout << "---------- Print Values ----------------";
	std::cout << "\n VR : " << this->VR
		<< "\n V0 : " << this->V0
		<< "\n DV : " << this->D_V
		<< "\n a= " << radians_to_degrees(this->a)
		<< "\n b= " << radians_to_degrees(this->b)
		<< "\n\n lamda= " << radians_to_degrees(this->lamda)
		<< "\n gamma= " << radians_to_degrees(this->gamma)
		<< "\n Rad gamma= " << (this->gamma)
		<< "\n Dgamma= " << radians_to_degrees(this->D_gamma)
		<< "\n m =" << radians_to_degrees(this->m)
		<< "\n theta= " << radians_to_degrees(this->theta)
		<< "\n fi= " << radians_to_degrees(this->fi)
		<< "\n psi= " << radians_to_degrees(this->psi)
		<< "\n\n distance=" << dist
		<< "\n Avoid dis =" << avoidance_distance
		<< "\n Safe dis =" << safe_distance
		<< "\n\n OBS_X: " << this->x_b << ", EXP_X: " << this->eccentric_expansion_x
		<< "\n OBS_Y: " << this->y_b << ", EXP_Y: " << this->eccentric_expansion_y
		<< "\n EXP_RADIUS:" << this->eccentric_expansion_radius

		<< "\n New Velocity:" << this->New_VR
		<< "\n M_DCPA: " << this->M_DCPA
		<< "\n M_TCPA " << this->M_TCPA
		<< "\n m_ : " << (M_DCPA + M_TCPA) / 2
		<< "\n zetta : " << radians_to_degrees(this->zetta) << endl;

	if (this->heads_on_mode) { std::cout << " MODE: HEADS ON MODE\n"; }
	else if (this->overtaking_mode) { std::cout << " MODE: OVERTAKING MODE\n"; }
	else { std::cout << " MODE:  CROSSING MODE\n"; }
	std::cout << "\n";
}
