#pragma once
#ifndef AREA_OBSTACLE_H
#define AREA_OBSTACLE_H

class Area_Obstacle {

private:
	double x;
	double y;
	double z;
	double radius;
	double distance;
	double velocity;
	double angle;
	std::string name;
	bool flag_1;
	char job;

public:

	Area_Obstacle(double x, double y, double z, double radius, double distance, std::string name, double velocity, double angle, bool flag) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->radius = radius;
		this->distance = distance;
		this->name = name;
		this->velocity = velocity;
		this->angle = angle;
		this->flag_1 = flag;
		this->job = 'N';
	}
	
	double get_x() {
		return this->x;
	}
	double get_y() {
		return this->y;
	}
	double get_z() {
		return this->z;
	}
	double get_radius() {
		return this->radius;
	}
	double get_distance() {
		return this->distance;
	}
	double get_velocity() {
		return this->velocity;
	}
	double get_angle() {
		return this->angle;
	}
	void set_flag_1(bool flag) {
		this->flag_1 = flag;
	}
	void set_job(char job) {
		this->job = job;
	}
	void set_xy(double x, double y) {
		this->x = x;
		this->y = y;
	}
	char get_job() {
		return this->job;
	}
	std::string get_name() {
		return this->name;
	}
	bool get_flag_1() {
		return this->flag_1;
	}

};

#endif
