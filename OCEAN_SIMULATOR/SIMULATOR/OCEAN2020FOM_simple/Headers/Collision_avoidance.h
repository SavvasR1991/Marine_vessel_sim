#pragma once
#ifndef COLLISION_AVOIDANCE_H
#define COLLISION_AVOIDANCE_H
#include <iostream>  
#include <algorithm>
#include "Geometry_Functions.h"

class Collision_Avoidance {

private:
	bool heads_on_mode,overtaking_mode,crossing_mode;
	bool collision_check_evaluation;
	bool emegercy_avoidance_val;

	double acc;
	double max_speed;
	double VR, VR_Previous, New_VR;
	double V0, V0_Previous;
	double a, a_Previous, ANGLE_INITIAL,d_A, ANGLUAL_ORIGINAL;
	double b, b_Previous;
	double gamma, gamma_Previous, D_gamma;
	double m,theta,h,lamda, psi, fi, fi_Previous, zetta;
	double D_original;
	double D_V, D_V_Previous;
	double x_a,y_a, z_a;
	double x_b,y_b, z_b, obs_y, obs_x;
	double dist, dist_previous,safe_distance,avoidance_distance;
	double collision_propability, M_DCPA , M_TCPA;
	double eccentric_expansion_radius, eccentric_expansion_radius_Previous;
	double eccentric_expansion_x, eccentric_expansion_x_Previous;
	double eccentric_expansion_y, eccentric_expansion_y_Previous;
	double acceleration, angular_velocity, radius_b;

	void Collision_Avoidance_Reset();
	bool check_range_estimator(double, double, double, double, double);
	void set_initial_movements(double v_a, double theta_a, double v_b, double theta_b);
	void set_vessel_possition(double x_a, double y_a, double z_a);
	void set_obstacle_possition(double x_b, double y_b, double z_b);
	void set_areas(double , double);
	void set_velocities_movements(double acceleration, double angular_speed,double max_speed);

	void check_encounter_collision_situation();
	void eccentric_expansion_circle();
	void geometrical_values_computation();
	void motion_rediractor();
	void estimate_collision();

	void update(double&, double&);

public:
	Collision_Avoidance();
	~Collision_Avoidance();

	bool collision_avoidance_start(double&, double&, double, double,double, double, double, double, double, double, double, double, double ,double,bool&,double);
	void check_eccentric_expansion(double&, double&,double&);
	void print_Collision_Values();
	void print_Values();

};

#endif